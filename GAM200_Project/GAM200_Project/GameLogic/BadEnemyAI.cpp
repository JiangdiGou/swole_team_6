#include "BadEnemyAI.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"
#include <cmath> 

//playerstate component for reference
void BadEnemyAI::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);

	player = parent->FindObject("GAMEPLAYER");
  if (player != NULL)
  {
    playerHM = player->has(HealthManager);

    pSprite = parent->has(Sprite);
    if (pSprite)
      pSprite->setLayer(1);
  }

  paceDistance = Vector3D(2,0,0);
  waitTime = 2;
  attackCooldown = 2;

  CanMove = true;
  CurrentState = PACING;


#ifdef EDITOR
  //CanMove = false;
#else
  CanMove = true;
#endif
}

void BadEnemyAI::Update(float dt)
{
	GOC* owner = GetOwner();
	Transform* playerTransform = player->has(Transform);
	
	if (attackCooldown > 0)
	{
		attackCooldown = attackCooldown - dt;
	}

  ////////////////////////////////////////////////////////        Movement          ////////////////////////////////////////////////////////////////
	if (CanMove)
	{
		if (CurrentState == PACING)
		{
			Vector3D temp = Vector3D(paceDistance.x * dt, 0, 0);

			if (MovingRight)
			{
				pTransform->SetPosition((pTransform->GetPosition() + temp));
			}
			else if (!MovingRight)
			{
				pTransform->SetPosition((pTransform->GetPosition() - temp));
			}

			if (waitTime > 0)
			{
				waitTime -= dt;
			}
			else
			{
				if (MovingRight)
				{
					MovingRight = false;
					//pTransform->SetScale(pTransform->GetScale() * (-1, 1, 1));
				}
				else
				{
					MovingRight = true;
					//pTransform->SetScale(pTransform->GetScale() * (-1,1,1));
				}

				waitTime = 2;
			}
		}
		else if (CurrentState == CHASING)
		{
			if ((pTransform->GetPositionX() - 1) > playerTransform->GetPositionX())
			{
				pTransform->SetPosition(Vector3(pTransform->GetPositionX() - (2 * dt), pTransform->GetPositionY(), 0));
			}
			else if((pTransform->GetPositionX() + 1) < playerTransform->GetPositionX())
			{
				pTransform->SetPosition(Vector3(pTransform->GetPositionX() + (2 * dt), pTransform->GetPositionY(), 0));
			}

		}
		else if (CurrentState == ATTACKING)
		{
			if (attackCooldown <= 0)
			{
				//change the sprite to attacking here
				std::cout << "ATTACK";
				playerHM->UpdateHealth(-5.0f);

				CurrentState = CHASING;
				attackCooldown = 2;
			}
		}
		else
		{
			CurrentState = PACING;
		}
////////////////////////////////////////////////////////        Chasing         ////////////////////////////////////////////////////////////////

		if (abs((pTransform->GetPositionX() - playerTransform->GetPositionX())) < 3)
		{
			CurrentState = CHASING;
		}

////////////////////////////////////////////////////////        Attacking        ////////////////////////////////////////////////////////////////
		//if were in range to attack
		if (abs((pTransform->GetPositionX() - playerTransform->GetPositionX())) < 0.5)
		{
			CurrentState = ATTACKING;
		}
	}


}

void BadEnemyAI::SendMessages(Message* message)
{
}

void BadEnemyAI::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

BadEnemyAI::BadEnemyAI()
{

}