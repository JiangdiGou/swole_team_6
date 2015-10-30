#include "PlayerState.h"

#define MORE_FRAME 0.02f
#define PER_FRAME 0.03f
#define DEATH_FRAME 1.5f

PlayerState::PlayerState() : //parent(),
//controller(new PlayerControllerListener(Parent, this, Controller)),
//keyboard(new PlayerKeyboardListener(Parent, this)),
//CollisionDelegate(),
MyPlayerState(Grounded), jumpCount(0), JumpTimer(0), IsAlive(true), DeathCount(0),
LastframeDT(1.0f / 60.0f), jumpButtonReleased(false)
{
  float *temp = NULL;
  Platform = NULL;
  WalkTimer = 0.0f;
  PreviousPlatformPosition.x = 0;
  PreviousPlatformPosition.y = 0;
  PreviousPlatformPosition.z = 0;

  // should we assign the value of each properties in the header file or here?
  // ok so I did that in the header file and removed the pointer
  

}

void PlayerState::Initialize()
{
  // we need messaging system here to connect the player controller first
  
  parent = GetOwner();
  //playerTileCollision = reinterpret_cast<TileMapCollision*>(parent->GetComponent(CT_TileMapCollision));
  playerBody = reinterpret_cast<Body *>(parent->GetComponent(CT_Body));
  //playerSpriteRend = reinterpret_cast<SpriteRenderer *>(parent->GetComponent(CT_SpriteRenderer));
 // we need to initialize the messaging system here!!

  //InitializeCollisionCallback();
  
  
}

PlayerState::~PlayerState()
{
    // where we should destruct the keyboard event if necessceary?
	
}
//
//
//// this function maybe should put into a input manager instead of the player controller. but who knows
//// I need a enum list for key button state like this
//// enum KEY_STATE{KEY_DOWN, KEY_RELEASED, KEY_TRIGGERED, KEY_UP}; in somewhere and can be integrate with
//// the messaging system
//
//// But since our game going to be mouse control mainly, the keyboard button maybe useless !!!
//
//
void PlayerState::SendMessages(Message * message)
{
	switch (message->MessageId)
	{
		// The user has pressed a (letter/number) key, we may respond by creating
		// a specific object based on the key pressed.
	case Mid::CharacterKey:
	{
		MessageCharacterKey* CharacterMessage = (MessageCharacterKey*)message;
		switch (CharacterMessage->character)
		{
		case 'W':
			if (CharacterMessage->keyStatus == keyStatus::KEY_PRESSED)
			{
				// we can do anything here also sounds

				//variableJumpHeightEnabled = true;
				PressJump();
				//playerBody->AddForce(Vec2D(0, 1000));
				printf("my jumping v: %f", playerBody->Velocity.y);
			}

			else if (CharacterMessage->keyStatus == keyStatus::KEY_RELEASED)
			{
				//change player sprite state here

				//variableJumpHeightEnabled = false;
				ReleaseJump();
			}
			else if (CharacterMessage->keyStatus == keyStatus::KEY_DOWN)
			{
				// do nothing

			}


			break;

		case 'S':
			// we don't need to down key anyway so do shit 
			break;

		case 'A':
			//if (this->playerController->getJumpState() == JumpStates::JS_Grounded || this->playerController->getJumpState() == JumpStates::JS_PLATFORM)
			//{
			//PlayerSprite->GetCurrentSprite()->Set_Paused(false);

			if (WalkTimer > 0.4 && getJumpTimer() < MORE_FRAME)
			{

				WalkTimer = 0.0f;
			}
			//}

			if (CharacterMessage->keyStatus == KEY_PRESSED || CharacterMessage->keyStatus == KEY_DOWN)
			{
				// change player sprite state here 
        Sprite* playerSprite = LOGIC->player->has(Sprite);
        playerSprite->texture = GRAPHICS->getSpriteAtlas()->textures["CharacterRun"];
        

				if (playerBody->Velocity.x >= 0.2f)
					break;

				playerBody->Velocity.x = -(playerRunSpeed);
				printf("vel while moving right: %f", playerBody->Velocity.x);
				//playerBody->AddForce(Vec2D(-50, 0));
				
				
				//Make the player face left
				/*		if (PlayerTransform->GetScale().x > 0)
						{
						PlayerTransform->GetScale().x *= -1.0f;
						}*/
			}

			if (CharacterMessage->keyStatus == KEY_RELEASED)
			{
				playerBody->AddForce(Vec2D(0,0));
				//PlayerSprite->ChangeState("idle");
				playerBody->Velocity.x = 0.0f;
				//playerBody->Friction = 0.0f; 
			}

			break;

		case 'D':

			// if the player is grounded and the player is pressing right, play move sound effect
			//if (this->playerController->getJumpState() == StateList::Grounded || this->playerController->getJumpState() == StateList::OnGround)
			//{
			// pause the player sprite state here

			if (WalkTimer > 0.4 && getJumpTimer() < MORE_FRAME)
			{

				WalkTimer = 0.0f;
			}
			//}

			// change sprite and flip sprite if necessary
			if (CharacterMessage->keyStatus == KEY_PRESSED || CharacterMessage->keyStatus == KEY_DOWN)
			{
				// we can change the player sprite to dashing or sth here?
        Sprite* playerSprite = LOGIC->player->has(Sprite);
        playerSprite->texture = GRAPHICS->getSpriteAtlas()->textures["CharacterRun"];

				if (playerBody->Velocity.x <= -0.2f)
					break;
				playerBody->Velocity.x = (playerRunSpeed);
			
				printf("lalal: %f", playerBody->Velocity.x);
				//playerBody->AddForce(Vec2D(50, 0));


				//if (PlayerTransform->GetScale().x < 0)
				//{
				//	//Face the player right
				//	PlayerTransform->GetScale().x *= -1.0f;
				//}
			}

			// revert changes when the key is released
			if (CharacterMessage->keyStatus == KEY_RELEASED)
			{
				//player should be idle here?

				playerBody->AddForce(Vec2D(0, 0));
				playerBody->Velocity.x = 0.0f;
				//playerBody->Friction = 0.0f;
			}

			break;
		}
	}
	}
}



void PlayerState::Update(float dt)
{
    LastframeDT = dt;
    JumpTimer += dt;
	WalkTimer += dt;

	//When player dies, stop for 2 seconds and then reload
	if (!IsAlive)
	{
		DeathCount += dt;
		if (DeathCount > DEATH_FRAME)
		{
			gGameStateCurr = GS_RESTART;
		}
		return;
	}

	//if (playerBody->Velocity.y < -(maxDownwardsVelocity))
	//	playerBody->SetVelocity(Vec2D(playerBody->Velocity.x, /*playerBody->Velocity.y +  */-(maxDownwardsVelocity)));
	//if (playerBody->Velocity.y > maxUpwardsVelocity)
		//playerBody->SetVelocity(Vec2D(playerBody->Velocity.x, /*playerBody->Velocity.y + */ 0));
	    

	//if (MyPlayerState == Gwrounded)
	//{
	//	if (playerTileCollision->BottomIsColliding())
	//		JumpTimer = 0;
	//	//playerBody->setVelocity(playerBody->getVelocity().x, 0);
	//	return;
	//}

	//if (MyPlayerState == OnGround)
	//{
	//	

	//	if (Platform != NULL)
	//	{
	//		
	//		Transform* Trans = GetOwner()->has(Transform);
	//		Transform* TransPlat = Platform->has(Transform);
	//		// apparently we need to use Gethas or whatever that is, GM help!
	//		float CheckXpos = abs(Trans->GetPosition().x - TransPlat->GetPosition().x);
	//		float CheckYpos = abs(Trans->GetPosition().y - TransPlat->GetPosition().y);


	//		if (CheckXpos < 1.0 && CheckYpos < 2.0)
	//		{
	//			// calculate how far the platform has moved
	//			float XDis = TransPlat->GetPosition().x - PreviousPlatformPosition.x;
	//			float YDis = TransPlat->GetPosition().y - PreviousPlatformPosition.y;


	//			playerBody->pTrans->GetPositionXY().x += XDis;
	//			Trans->GetPosition().x += XDis;

	//			float PlatformYVelocity = ((RigidBody*)Platform->GetComponent(CT_RigidBody))->getVelocity().y;
	//			float PlatformXVelocity = ((RigidBody*)Platform->GetComponent(CT_RigidBody))->getVelocity().x;

	//			playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + PlatformYVelocity);

	//			if (YDis <= 0)
	//			{
	//				playerBody->pTrans->GetPositionXY().y += YDis;
	//				Trans->GetPosition().y += YDis;
	//			}
	//			// move the player with the platform
	//			PreviousPlatformPosition = TransPlat->GetPosition();

	//		}

	//		else
	//		{
	//			Platform = NULL;

	//		
	//		}

	//	}
	//}


	// On the ground
	//if (playerTileCollision->BottomIsColliding() && JumpTimer > PER_FRAME)
	//{
	//	jumpCount = 0;
	//	JumpTimer = 0;
	//	MyPlayerState = Grounded;
	//	jumpButtonReleased = false;
	//	return;
	//}

	////Keep our variable-height jump going up to the max height
	//if (MyPlayerState == StartJump)
	//{
	//	playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + (playerJumpVelocity * (variableJumpPower)));

	//	//At max height, stop our variable jump.
	//	if (JumpTimer > variableJumpTime)
	//	{
	//		JumpTimer = 0;
	//		MyPlayerState = Jumping;
	//	}

	//}



}

void PlayerState::Release()
{

}

void PlayerState::PressJump()
{
	if (!IsAlive)
		return;

	/*if ((MyPlayerState == Grounded || MyPlayerState == OnGround) && (playerTileCollision->BottomIsColliding() || JumpTimer < timeToJumpAfterLeftGround))
	{
		if (variableJumpHeightEnabled)
			MyPlayerState = StartJump;
		else
			MyPlayerState = Jumping;

		 if(variableJumpHeightEnabled)*/
		if (variableJumpHeightEnabled)
			playerBody->SetVelocity(Vec2D(playerBody->Velocity.x, (playerJumpVelocity * (variableJumpPower))));//playerBody->Velocity.y + (playerJumpVelocity * (variableJumpPower))));
		else
			playerBody->SetVelocity(Vec2D(playerBody->Velocity.x, playerBody->Velocity.y + playerJumpVelocity));


			
		JumpTimer = 0.0f;
		++jumpCount;
		return;
	//}
}

void PlayerState::ReleaseJump()
{
	//A: If we have variable jump height, switch us to the upward state
	if (!variableJumpHeightEnabled)
	{
		//myJumpState = JS_Jumping;
		playerBody->Velocity.y = playerJumpVelocity;
		//playerBody->Velocity.y = 0;
		jumpButtonReleased = true;
	}
}

void PlayerState::OnCollision(GameObjectComposition* someObject)
{
	
	//if ((someObject->GetComponent(CT_MOVEPLATFORM)) && JumpTimer > MORE_FRAME)
	//{
	//	MyPlayerState = Grounded;
	//	JumpTimer = 0;
	//	Platform = someObject;
	//	Transform* TransSO = someObject->has(Transform);
	//	PreviousPlatformPosition = TransSO->GetPosition();
	//	jumpButtonReleased = false;
	//}

	//if ((someObject->GetComponent(CT_SPAWNBLOCK) || someObject->GetComponent(CT_DESTROY)) && JumpTimer > MORE_FRAME)
	//{
	//	MyPlayerState = Grounded;
	//	JumpTimer = 0;
	//	jumpButtonReleased = false;
	//}

	////If we hit a "DIE, JUST DIE" object, reload at maybe a checkpoint????
	////(after 2 seconds- see the beginning of Update)
	//if (someObject->GetComponent(CT_PLAYERDEATH))
	//{
	//	ripPlayer();
	//}
}

void PlayerState::ripPlayer()
{	
	IsAlive = false;
}

int PlayerState::getJumpState(void)
{
	return MyPlayerState;
}


float PlayerState::getJumpTimer(void)
{
	return JumpTimer;
}