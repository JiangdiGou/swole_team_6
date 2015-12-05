#include "PlayerAttack.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"
#include "EnemyHealthManager.h"

//playerstate component for reference
void PlayerAttack::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

#ifdef EDITOR
  //CanMove = false;
#else
  //CanMove = true;
#endif
}

void PlayerAttack::Update(float dt)
{
}

void PlayerAttack::Attack(std::vector <GameObjectComposition*> objectsHit)
{
  for (std::vector<GameObjectComposition*>::iterator it = objectsHit.begin(); it != objectsHit.end(); ++it)
  {
    if ((*it)->GetName() == "Enemy ")
    {
      GOC *refedEnemy = (*it);
      EnemyHealthManager *refedEHM = refedEnemy->has(EnemyHealthManager);
      refedEHM->UpdateHealth(-20);
    }
  }
}

void PlayerAttack::SendMessages(Message* message)
{
}

void PlayerAttack::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

PlayerAttack::PlayerAttack()
{

}