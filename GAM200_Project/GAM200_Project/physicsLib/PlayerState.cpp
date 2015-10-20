//#include "PlayerState.h"
//
//#define MORE_FRAME 0.02f
//#define PER_FRAME 0.03f
//PlayerState::PlayerState() ://: parent(Parent),,
////controller(new PlayerControllerListener(Parent, this, Controller)),
////keyboard(new PlayerKeyboardListener(Parent, this)),
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
//  
//
//}
//
//void PlayerState::Initialize()
//{
//  // we need messaging system here to connect the player controller first
//  
//  
//  playerTileCollision = reinterpret_cast<TileMapCollision*>(parent->GetComponent(CT_TileMapCollider));
//  playerBody = reinterpret_cast<RigidBody *>(parent->GetComponent(CT_RigidBody));
//  //playerSpriteRend = reinterpret_cast<SpriteRenderer *>(parent->GetComponent(CT_SpriteRenderer));
// // we need to initialize the messaging system here!!
//
//  InitializeCollisionCallback();
//  
//  
//}
//
//PlayerState::~PlayerState()
//{
//    // same things we should put in the last function for the messaging system call
//}
//
//void PlayerState::SendMessages(Message * message)
//{
//
//}
//
//void PlayerState::Update(float dt)
//{
//    LastframeDT = dt;
//    JumpTimer += dt;
//	WalkTimer += dt;
//
//	if (playerBody->getVelocity().y < -(maxDownwardsVelocity))
//		playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + -(maxDownwardsVelocity));
//	if (playerBody->getVelocity().y > maxUpwardsVelocity)
//		playerBody->setVelocity(playerBody->getVelocity().x, playerBody->getVelocity().y + (maxUpwardsVelocity));
//
//	if (MyPlayerState == Grounded)
//	{
//		if (playerTileCollision->BottomIsColliding())
//			JumpTimer = 0;
//
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