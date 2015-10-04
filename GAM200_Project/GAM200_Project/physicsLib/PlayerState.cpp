#include "PlayerState.h"


#define PER_FRAME 0.03f
PlayerState::PlayerController(GameObjectComposition Parent, int Controller) : parent(Parent),
IComponent(Component_Type::CT_Player_Controller, Parent),
CollisionDelegate(Parent),
controller(new PlayerControllerListener(Parent, this, Controller)),
keyboard(new PlayerKeyboardListener(Parent, this)),
myJumpState(Grounded), jumpCount(0), JumpTimer(0), IsAlive(true), DeathCount(0),
lastFrameDT(1.0f / 60.0f), jumpButtonReleased(false)
{
  float *temp = NULL;

  Platform = NULL;
  WalkTimer = 0.0f;
  PreviousPlatformPosition.x = 0;
  PreviousPlatformPosition.y = 0;
  PreviousPlatformPosition.z = 0;

  // should we assign the value of each properties in the header file or here?
  

}

void PlayerState::Initialize()
{
  // we need messaging system here to connect the player controller first
  
  
  playerTileCollision = reinterpret_cast<TileMapCollision*>(parent->GetComponent(CT_TileMapCollider));
  playerBody = reinterpret_cast<RigidBody *>(parent->GetComponent(CT_Body));
  //playerSpriteRend = reinterpret_cast<SpriteRenderer *>(parent->GetComponent(CT_SpriteRenderer));
 // we need to initialize the messaging system here!!

  InitializeCollisionCallback();
  
  
}

PlayerState::~PlayerController()
{
    // same things we should put in the last function for the messaging system call
}

void PlayerState::Update(float dt)
{
    LastframeDT = dt;
    JumpTimer += dt;
	WalkTimer += dt;

	if (playerBody->velocity.y < -(*maxDownwardsVelocity))
		playerBody->velocity.y = -(*maxDownwardsVelocity);
	if (playerBody->velocity.y > *maxUpwardsVelocity)
		playerBody->velocity.y = *maxUpwardsVelocity;

	if (MyPlayerState == Grounded)
	{
		if (playerTileCollision->BottomIsColliding())
			JumpTimer = 0;

		return;
	}

	if (MyPlayerState == OnGround)
	{
		

		if (Platform != NULL)
		{

			// apparently we need to use Gethas or whatever that is, GM help!
			float CheckXpos = abs(Owner->GetTransform()->GetPosition().x - Platform->GetTransform()->GetPosition().x);
			float CheckYpos = abs(Owner->GetTransform()->GetPosition().y - Platform->GetTransform()->GetPosition().y);


			if (CheckXpos < 1.0 && CheckYpos < 2.0)
			{
				// calculate how far the platform has moved
				float XDis = Platform->GetTransform()->GetPosition().x - PreviousPlatformPosition.x;
				float YDis = Platform->GetTransform()->GetPosition().y - PreviousPlatformPosition.y;


				playerBody->position.x += XDis;
				Owner->GetTransform()->GetPosition().x += XDis;

				float PlatformYVelocity = ((RigidBody*)Platform->GetComponent(CT_Body))->velocity.y;
				float PlatformXVelocity = ((RigidBody*)Platform->GetComponent(CT_Body))->velocity.x;

				playerBody->velocity.y = PlatformYVelocity;

				if (YDis <= 0)
				{
					playerBody->position.y += YDis;
					Owner->GetTransform()->GetPosition().y += YDis;
				}
				// move the player with the platform
				PreviousPlatformPosition = Platform->GetTransform()->GetPosition();

			}

			else
			{
				Platform = NULL;

			
			}

		}
	}

	if (playerTileCollision->BottomIsColliding() && JumpTimer > PER_FRAME)
	{
		jumpCount = 0;
		JumpTimer = 0;
		MyPlayerState = Grounded;
		jumpButtonReleased = false;
		return;
	}
	//Keep our variable-height jump going up to the max height
	if (MyPlayerState == StartJump)
	{
		playerBody->velocity.y = *playerJumpVelocity * (*variableJumpPower);

		//At max height, stop our variable jump.
		if (JumpTimer > *variableJumpTime)
		{
			JumpTimer = 0;
			MyPlayerState = Jumping;
		}

	}



}

void PlayerState::Release()
{

}

void PlayerState::PressJump()
{
	if (!IsAlive)
		return;

	if ((MyPlayerState == Grounded || MyPlayerState == OnGround) && (playerTileCollision->BottomIsColliding() || JumpTimer < *timeToJumpAfterLeftGround))
	{
		if (*variableJumpHeightEnabled)
			MyPlayerState = StartJump;
		else
			MyPlayerState = Jumping;

		if (*variableJumpHeightEnabled)
			playerBody->velocity.y = *playerJumpVelocity * (*variableJumpPower);
		else
			playerBody->velocity.y = *playerJumpVelocity;

		JumpTimer = 0.0f;
		++jumpCount;
		return;
	}
}


int PlayerState::getJumpState(void)
{
	return MyPlayerState;
}



float PlayerState::getJumpTimer(void)
{
	return JumpTimer;
}