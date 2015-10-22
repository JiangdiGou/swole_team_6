//#include "PlayerState.h"
//
//#define MORE_FRAME 0.02f
//#define PER_FRAME 0.03f
//#define DEATH_FRAME 1.5f
//
//PlayerState::PlayerState() : //parent(),
////controller(new PlayerControllerListener(Parent, this, Controller)),
////keyboard(new PlayerKeyboardListener(Parent, this)),
////CollisionDelegate(),
//MyPlayerState(Grounded), jumpCount(0), JumpTimer(0), IsAlive(true), DeathCount(0),
//LastframeDT(1.0f / 60.0f), jumpButtonReleased(false)
//{
//  float *temp = NULL;
//  Platform = NULL;
//  WalkTimer = 0.0f;
//  PreviousPlatformPosition.x = 0;
//  PreviousPlatformPosition.y = 0;
//  PreviousPlatformPosition.z = 0;
//
//  // should we assign the value of each properties in the header file or here?
//  // ok so I did that in the header file and removed the pointer
//  
//
//}
//
//void PlayerState::Initialize()
//{
//  // we need messaging system here to connect the player controller first
//  
//  parent = GetOwner();
//  playerTileCollision = reinterpret_cast<TileMapCollision*>(parent->GetComponent(CT_TileMapCollision));
//  playerBody = reinterpret_cast<RigidBody *>(parent->GetComponent(CT_RigidBody));
//  //playerSpriteRend = reinterpret_cast<SpriteRenderer *>(parent->GetComponent(CT_SpriteRenderer));
// // we need to initialize the messaging system here!!
//
//  //InitializeCollisionCallback();
//  
//  
//}
//
//PlayerState::~PlayerState()
//{
//    // where we should destruct the keyboard event if necessceary?
//	
//}
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
//void PlayerState::SendMessages(Message * message)
//{
//	//KeyMessage * GivenInput = reinterpret_cast<KeyMessage *>(SentMessage);
//
//	//switch (GivenInput->KeyNumber)
//	//{
//	//case VK_UP:
//	//	if (GivenInput->KeyStatus == KEY_STATE::KEY_TRIGGERED)
//	//	{
//	//		// we can do anything here also sounds
//
//	//		if (this->playerController->getJumpState() == StateList::Grounded)
//	//		{
//	//			// pause player sprite state here
//	//		}
//
//	//		playerController->PressJump();
//	//	}
//
//	//	else if (GivenInput->KeyStatus == KEY_STATE::KEY_RELEASED)
//	//	{
//	//		//change player sprite state here
//
//
//	//		playerController->ReleaseJump();
//	//	}
//	//	else if (GivenInput->KeyStatus == KEY_STATE::KEY_DOWN)
//	//	{
//	//		// do nothing
//
//	//	}
//
//
//	//	break;
//
//	//case VK_DOWN:
//	//	// we don't need to down key anyway 
//	//	break;
//
//	//case VK_LEFT:
//	//	if (this->playerController->getJumpState() == JumpStates::JS_Grounded || this->playerController->getJumpState() == JumpStates::JS_PLATFORM)
//	//	{
//	//		//PlayerSprite->GetCurrentSprite()->Set_Paused(false);
//
//	//		if (this->playerController->WalkTimer > 0.4 && this->playerController->getJumpTimer() < MORE_FRAME)
//	//		{
//
//	//			this->playerController->WalkTimer = 0.0f;
//	//		}
//	//	}
//
//	//	if (GivenInput->KeyStatus == KEY_TRIGGERED || GivenInput->KeyStatus == KEY_DOWN)
//	//	{
//	//		// change player sprite state here 
//
//
//	//		playerBody->getVelocity().x = -(*playerController->playerRunSpeed);
//
//	//		//Make the player face left
//	//		if (PlayerTransform->GetScale().x > 0)
//	//		{
//	//			PlayerTransform->GetScale().x *= -1.0f;
//	//		}
//	//	}
//
//	//	if (GivenInput->KeyStatus == KEY_RELEASED)
//	//	{
//	//		PlayerSprite->ChangeState("idle");
//	//		playerBody->getVelocity().x = 0.0f;
//	//	}
//
//	//	break;
//
	////case VK_RIGHT:

	////	// if the player is grounded and the player is pressing right, play move sound effect
	////	if (this->playerController->getJumpState() == StateList::Grounded || this->playerController->getJumpState() == StateList::OnGround)
	////	{
	////		// pause the player sprite state here

	////		if (this->playerController->WalkTimer > 0.4 && this->playerController->getJumpTimer() < MORE_FRAME)
	////		{

	////			this->playerController->WalkTimer = 0.0f;
	////		}
	////	}

	////	// change sprite and flip sprite if necessary
	////	if (GivenInput->KeyStatus == KEY_TRIGGERED || GivenInput->KeyStatus == KEY_DOWN)
	////	{
	////		// we can change the player sprite to dashing or sth here?


	////		playerBody->getVelocity().x = *playerController->playerRunSpeed;

	////		if (PlayerTransform->GetScale().x < 0)
	////		{
	////			//Face the player right
	////			PlayerTransform->GetScale().x *= -1.0f;
	////		}
	////	}

	////	// revert changes when the key is released
	////	if (GivenInput->KeyStatus == KEY_RELEASED)
	////	{
	////		//player should be idle here?


	////		playerBody->getVelocity().x = 0.0f;
	////	}

	////	break;
	////}
//
//}
//
//void PlayerState::Update(float dt)
//{
//    LastframeDT = dt;
//    JumpTimer += dt;
//	WalkTimer += dt;
//
//	//When player dies, stop for 2 seconds and then reload
//	if (!IsAlive)
//	{
//		DeathCount += dt;
//		if (DeathCount > DEATH_FRAME)
//		{
//			gGameStateCurr = GS_RESTART;
//		}
//		return;
//	}
//
//	if (playerBody->getVelocity().y < -(maxDownwardsVelocity))
//		playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + -(maxDownwardsVelocity));
//	if (playerBody->getVelocity().y > maxUpwardsVelocity)
//		playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + (maxUpwardsVelocity));
//	    
//
//	if (MyPlayerState == Grounded)
//	{
//		if (playerTileCollision->BottomIsColliding())
//			JumpTimer = 0;
//		//playerBody->setVelocity(playerBody->getVelocity().x, 0);
//		return;
//	}
//
//	if (MyPlayerState == OnGround)
//	{
//		
//
//		if (Platform != NULL)
//		{
//			
//			Transform* Trans = GetOwner()->has(Transform);
//			Transform* TransPlat = Platform->has(Transform);
//			// apparently we need to use Gethas or whatever that is, GM help!
//			float CheckXpos = abs(Trans->GetPosition().x - TransPlat->GetPosition().x);
//			float CheckYpos = abs(Trans->GetPosition().y - TransPlat->GetPosition().y);
//
//
//			if (CheckXpos < 1.0 && CheckYpos < 2.0)
//			{
//				// calculate how far the platform has moved
//				float XDis = TransPlat->GetPosition().x - PreviousPlatformPosition.x;
//				float YDis = TransPlat->GetPosition().y - PreviousPlatformPosition.y;
//
//
//				playerBody->pTrans->GetPositionXY().x += XDis;
//				Trans->GetPosition().x += XDis;
//
//				float PlatformYVelocity = ((RigidBody*)Platform->GetComponent(CT_RigidBody))->getVelocity().y;
//				float PlatformXVelocity = ((RigidBody*)Platform->GetComponent(CT_RigidBody))->getVelocity().x;
//
//				playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + PlatformYVelocity);
//
//				if (YDis <= 0)
//				{
//					playerBody->pTrans->GetPositionXY().y += YDis;
//					Trans->GetPosition().y += YDis;
//				}
//				// move the player with the platform
//				PreviousPlatformPosition = TransPlat->GetPosition();
//
//			}
//
//			else
//			{
//				Platform = NULL;
//
//			
//			}
//
//		}
//	}
//
//
//	// On the ground
//	if (playerTileCollision->BottomIsColliding() && JumpTimer > PER_FRAME)
//	{
//		jumpCount = 0;
//		JumpTimer = 0;
//		MyPlayerState = Grounded;
//		jumpButtonReleased = false;
//		return;
//	}
//
//	//Keep our variable-height jump going up to the max height
//	if (MyPlayerState == StartJump)
//	{
//		playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + (playerJumpVelocity * (variableJumpPower)));
//
//		//At max height, stop our variable jump.
//		if (JumpTimer > variableJumpTime)
//		{
//			JumpTimer = 0;
//			MyPlayerState = Jumping;
//		}
//
//	}
//
//
//
//}
//
//void PlayerState::Release()
//{
//
//}
//
//void PlayerState::PressJump()
//{
//	if (!IsAlive)
//		return;
//
//	if ((MyPlayerState == Grounded || MyPlayerState == OnGround) && (playerTileCollision->BottomIsColliding() || JumpTimer < timeToJumpAfterLeftGround))
//	{
//		if (variableJumpHeightEnabled)
//			MyPlayerState = StartJump;
//		else
//			MyPlayerState = Jumping;
//
//		if (variableJumpHeightEnabled)
//			playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + (playerJumpVelocity * (variableJumpPower)));
//		else
//			playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + playerJumpVelocity);
//
//		JumpTimer = 0.0f;
//		++jumpCount;
//		return;
//	}
//}
//
//void PlayerState::OnCollision(GameObjectComposition* someObject)
//{
//	
//	if ((someObject->GetComponent(CT_MOVEPLATFORM)) && JumpTimer > MORE_FRAME)
//	{
//		MyPlayerState = Grounded;
//		JumpTimer = 0;
//		Platform = someObject;
//		Transform* TransSO = someObject->has(Transform);
//		PreviousPlatformPosition = TransSO->GetPosition();
//		jumpButtonReleased = false;
//	}
//
//	if ((someObject->GetComponent(CT_SPAWNBLOCK) || someObject->GetComponent(CT_DESTROY)) && JumpTimer > MORE_FRAME)
//	{
//		MyPlayerState = Grounded;
//		JumpTimer = 0;
//		jumpButtonReleased = false;
//	}
//
//	//If we hit a "DIE, JUST DIE" object, reload at maybe a checkpoint????
//	//(after 2 seconds- see the beginning of Update)
//	if (someObject->GetComponent(CT_PLAYERDEATH))
//	{
//		ripPlayer();
//	}
//}
//
//void PlayerState::ripPlayer()
//{	
//	IsAlive = false;
//}
//
//int PlayerState::getJumpState(void)
//{
//	return MyPlayerState;
//}
//
//
//float PlayerState::getJumpTimer(void)
//{
//	return JumpTimer;
//}