#include "PlayerAttack.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

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

void PlayerAttack::Attack()
{

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