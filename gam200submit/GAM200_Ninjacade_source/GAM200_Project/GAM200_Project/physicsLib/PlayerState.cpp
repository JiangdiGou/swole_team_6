/*****************************************************************************/
/*!
\file    PlayerState.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
The implementation for the player controller. 
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

#include "PlayerState.h"

#define MORE_FRAME 0.02f
#define PER_FRAME 0.03f
#define DEATH_FRAME 1.5f

PlayerState::PlayerState() : 
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
  playerSound = reinterpret_cast<SoundEmitter *>(parent->GetComponent(CT_SoundEmitter));
  //InitializeCollisionCallback();
  playerTransform = reinterpret_cast<Transform *>(parent->GetComponent(CT_Transform));
  playerSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));
  //Getting actual ptr here on purpose. No one should ever fuck w/ player sprite
  //Except this script. 
  idleAnimation = &(GRAPHICS->getSpriteAtlas()->textures["Character"]);
  runAnimation = &(GRAPHICS->getSpriteAtlas()->textures["CharacterRun"]);

  

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
  
  if (AutoPlayOn == true)
  {
    int rand_index = 0;
    static char randominput[] = { 'W', 'S', 'D', 'A', ' ' };
    if (AutoPlayTimer <= 0)
    {
      srand(time(0));

      rand_index = rand() % 5;
      AutoPlayTimer = AutoPlayTimerMax;
      curAuto = randominput[rand_index];
    }
    MessageCharacterKey keyMsg;

    keyMsg.character = curAuto;
    if (AutoPlayTimer < 50)
    {
      keyMsg.keyStatus = keyStatus::KEY_RELEASED;
    }
    else
    {
      keyMsg.keyStatus = keyStatus::KEY_PRESSED;
    }
    std::cout << randominput[rand_index] << std::endl;

    SendMessages(&keyMsg);
    --AutoPlayTimer;
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


	//On the ground

	//if (playerTileCollision->BottomIsColliding() )//&& JumpTimer > PER_FRAME)
	//{
	//jumpCount = 0;
	//JumpTimer = 0;
	//MyPlayerState = Grounded;
	//jumpButtonReleased = false;
	//return;
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
		case 'P':
			if (CharacterMessage->keyStatus == keyStatus::KEY_PRESSED)
			{
				playerSound->BeQuiet();
			}
			else if (CharacterMessage->keyStatus == keyStatus::KEY_RELEASED)
			{

			}
			else if (CharacterMessage->keyStatus == keyStatus::KEY_DOWN)
			{
				playerSound->Rock();
			}
			break;
		
	     
		case 'Z':
			if (CharacterMessage->keyStatus == keyStatus::KEY_PRESSED)
			{
				playerSound->SetVolume(1.0f,"SwordHitOrganic");
				playerSound->StopEvent("SwordHitOrganic");
				playerSound->PlayEvent("SwordHitOrganic");

			}
			else if (CharacterMessage->keyStatus == keyStatus::KEY_RELEASED)
			{
				
			}
		case VK_SPACE:
			//if (StateList::Grounded)
			//{
			if ((CharacterMessage->keyStatus == keyStatus::KEY_PRESSED || CharacterMessage->keyStatus == KEY_DOWN) && (MyPlayerState == StateList::Grounded || IWannaFly == true))
				{
					playerSound->SetVolume(1.0f, "TwoFootSteps");
					playerSound->StopEvent("TwoFootSteps");
					playerSound->PlayEvent("TwoFootSteps");
					
			
					// we can do anything here also sounds

					//variableJumpHeightEnabled = true;
          MyPlayerState = StateList::Jumping;
					PressJump();
					//playerBody->AddForce(Vec2D(0, 1000));
					printf("my jumping v: %f", playerBody->Velocity.y);
				}

				else if (CharacterMessage->keyStatus == keyStatus::KEY_RELEASED)
				{
					//change player sprite state here
          //There is no jump animation yet 

					//variableJumpHeightEnabled = false;
					//ReleaseJump();
					playerSound->SetPause(true, "TwoFootSteps");
	                
					
				}
				//else if (CharacterMessage->keyStatus == keyStatus::KEY_DOWN)
				//{
					// do nothing
					
				//}
			//}
      break;
		case 'S':
			break;
    case '0':
      AutoPlayOn = true;
      break;
    case '9':
      AutoPlayOn = false;
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

			if (CharacterMessage->keyStatus == KEY_PRESSED )//|| CharacterMessage->keyStatus == KEY_DOWN)
			{
				
				//playerSound->StopEvent("player_footsteps");
				playerSound->SetVolume(1.0f, "TwoFootSteps");
				playerSound->StopEvent("TwoFootSteps");
				playerSound->PlayEvent("TwoFootSteps");
				
				
				JumpTimer = 0.0f;

				printf("reach sound");
				// change player sprite state here 
        if (playerSprite->texture != *runAnimation)
          playerSprite->texture = *runAnimation;

        if (playerTransform->GetScale().x > 0)
        {
          playerTransform->SetScale(Vector2(-1 * playerTransform->GetScale().x,
            playerTransform->GetScale().y));
        }


				if (playerBody->Velocity.x >= 0.2f)
					break;

				playerBody->Velocity.x = -(playerRunSpeed);
				//printf("vel while moving right: %f", playerBody->Velocity.x);
				//playerBody->AddForce(Vec2D(-50, 0));
				
				
				//Make the player face left
				/*		if (PlayerTransform->GetScale().x > 0)
						{
						PlayerTransform->GetScale().x *= -1.0f;
						}*/
			}

			else if (CharacterMessage->keyStatus == KEY_RELEASED)
			{

				playerSound->SetPause(true, "TwoFootSteps");
				
				playerBody->AddForce(Vec2D(0,0));
				//PlayerSprite->ChangeState("idle");
				playerBody->Velocity.x = 0.0f;
				
				//playerBody->Friction = 0.0f; 

        if (playerSprite->texture != *idleAnimation)
          playerSprite->texture = *idleAnimation;
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
			/*
				// This will start the sound loop.
				if (CharacterMessage->KeyStatus == Key_Pressed)
					playerSound->PlayEvent("swipe_sound");
				if (CharacterMessage->KeyStatus == KEY_RELEASED)
					playerSound->StopEvent("swipe_sound");
			*/
			//if (CharacterMessage->keyStatus == KEY_PRESSED || CharacterMessage->keyStatus == KEY_DOWN)
			if (CharacterMessage->keyStatus == KEY_PRESSED )//|| CharacterMessage->keyStatus == KEY_DOWN)
			{
				playerSound->SetVolume(1.0f, "TwoFootSteps");
				playerSound->StopEvent("TwoFootSteps");
				playerSound->PlayEvent("TwoFootSteps");
				
				// we can change the player sprite to dashing or sth here?
        if (playerSprite->texture != *runAnimation)
          playerSprite->texture = *runAnimation;

        if (playerTransform->GetScale().x < 0)
        {
          playerTransform->SetScale(Vector2(-1 * playerTransform->GetScale().x,
            playerTransform->GetScale().y));
        }

				if (playerBody->Velocity.x <= -0.2f)
					break;
				playerBody->Velocity.x = (playerRunSpeed);
			
				//printf("lalal: %f", playerBody->Velocity.x);
				//playerBody->AddForce(Vec2D(50, 0));

				/*
				if (playerBody->tx->etScale().x < 0)
				{
					//Face the player right
					playerBody->tx->SetScale().x *
				}
				*/
			}

			// revert changes when the key is released
			else if (CharacterMessage->keyStatus == KEY_RELEASED)
			{
				//player should be idle here?
				playerSound->SetPause(true, "TwoFootSteps");
				playerBody->AddForce(Vec2D(0, 0));
				playerBody->Velocity.x = 0.0f;
				//playerBody->Friction = 0.0f;

        if (playerSprite->texture != *idleAnimation)
          playerSprite->texture = *idleAnimation;
			}

			break;
    case '1':
      if (IsAltHeld() && IsCtrlHeld())
      {
        IWannaFly = true;
      }
      break;
    case '.':
      if (IsAltHeld() && IsCtrlHeld())
      {
        IWannaFly = false;
      }
      break;
		}
    break;
	}
  case Mid::CollisionStarted:
  {
    //GameObjectComposition* otherObj = ((CollisionStarted*)message)->otherObj->GetOwner();
    //std::cout << "start " << otherObj->GetName() << std::endl;
    MyPlayerState = StateList::Grounded;
    break;
  }
  case Mid::CollisionPersisted:
  {
    //GameObjectComposition* otherObj = ((CollisionPersisted*)message)->otherObj->GetOwner();
    //std::cout << "??? " << otherObj->GetName() << std::endl;
    MyPlayerState = StateList::Grounded;
    break;
  }
  case Mid::CollisionEnded:
  {
    //GameObjectComposition* otherObj = ((CollisionEnded*)message)->otherObj->GetOwner();
    //std::cout << "end " << otherObj->GetName() << std::endl;
    break;
  }
	}
}
void PlayerState::SerializeRead(Serializer& str)
{
  StreamRead(str,PreviousPlatformPosition);
  StreamRead(str, variableJumpHeightEnabled);
  StreamRead(str, (int&)jumpCount);
  StreamRead(str, JumpTimer);
  StreamRead(str, variableJumpTime);
  StreamRead(str, variableJumpPower);
  StreamRead(str, maxDownwardsVelocity);
  StreamRead(str, maxUpwardsVelocity);
  StreamRead(str, jumpButtonReleased); 

  StreamRead(str, LastframeDT);
  StreamRead(str, IsAlive);
  StreamRead(str, DeathCount);
  StreamRead(str, timeToJumpAfterLeftGround);
}
void PlayerState::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
  StreamWrite(str, PreviousPlatformPosition);
  StreamWrite(str);
  StreamWrite(str, variableJumpHeightEnabled);
  StreamWrite(str);
  StreamWrite(str, (int&)jumpCount);
  StreamWrite(str);
  StreamWrite(str, JumpTimer);
  StreamWrite(str);
  StreamWrite(str, variableJumpTime);
  StreamWrite(str);
  StreamWrite(str, variableJumpPower);
  StreamWrite(str);
  StreamWrite(str, maxDownwardsVelocity);
  StreamWrite(str);
  StreamWrite(str, maxUpwardsVelocity);
  StreamWrite(str);
  StreamWrite(str, jumpButtonReleased);
  StreamWrite(str);

  StreamWrite(str, LastframeDT);
  StreamWrite(str);
  StreamWrite(str, IsAlive);
  StreamWrite(str);
  StreamWrite(str, DeathCount);
  StreamWrite(str);
  StreamWrite(str, timeToJumpAfterLeftGround);
  StreamWrite(str);
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
ZilchDefineExternalType(StateList, "StateList", ZLib_Internal, builder, type)
{
  ZilchBindEnum(builder, type, SpecialType::Enumeration);
  ZilchBindEnumValue(builder, type, StateList::Grounded, "Grounded");
  ZilchBindEnumValue(builder, type, StateList::Jumping, "Jumping");
  ZilchBindEnumValue(builder, type, StateList::OnGround, "OnGround");
  ZilchBindEnumValue(builder, type, StateList::StartJump, "StartJump");
}
ZilchDefineType(PlayerState, "PlayerState", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindMethod(builder, type, &PlayerState::PressJump, ZilchNoOverload, "PressJump", ZilchNoNames);
  //ZilchBindMethod(builder, type, &PlayerState::HoldJump, ZilchNoOverload, "HoldJump", ZilchNoNames);
  ZilchBindMethod(builder, type, &PlayerState::ripPlayer, ZilchNoOverload, "ripPlayer", ZilchNoNames);
  ZilchBindMethod(builder, type, &PlayerState::getJumpState, ZilchNoOverload, "getJumpState", ZilchNoNames);
  ZilchBindMethod(builder, type, &PlayerState::getJumpTimer, ZilchNoOverload, "getJumpTimer", ZilchNoNames);

  ZilchBindField(builder, type, &PlayerState::playerRunSpeed, "playerRunSpeed", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &PlayerState::playerJumpVelocity, "playerJumpVelocity", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &PlayerState::WalkTimer, "WalkTimer", PropertyBinding::GetSet);

}