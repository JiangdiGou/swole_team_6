#include "BadEnemyAI.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void BadEnemyAI::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);

  Sprite *pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  paceDistance = Vector3D(5,0,0);
  waitTime = 2;
}

void BadEnemyAI::Update(float dt)
{
	GOC* owner = GetOwner();

  ////////////////////////////////////////////////////////        Movement          ////////////////////////////////////////////////////////////////
  Vector3D temp = Vector3D(paceDistance.x * dt, 0, 0);

  if (MovingRight)
  {
    pTransform->SetPosition((pTransform->GetPosition() + temp));
  }
  else if(!MovingRight)
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
    }
    else
    {
      MovingRight = true;
    }
    waitTime = 2;
  }

  ////////////////////////////////////////////////////////        Health          ////////////////////////////////////////////////////////////////
}

void BadEnemyAI::UpdateHealth(int val)
{

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