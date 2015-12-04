#include "PlayerHealthBar.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void PlayerHealthBar::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);

	player = LOGIC->player;

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

#ifdef EDITOR
  //CanMove = false;
#else
  //CanMove = true;
#endif
}

void PlayerHealthBar::Update(float dt)
{
	GOC* owner = GetOwner();
}

void PlayerHealthBar::UpdateScale(float scale)
{
  pTransform->SetScale(pTransform->GetScale() * scale);
}

void PlayerHealthBar::SendMessages(Message* message)
{
}

void PlayerHealthBar::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

PlayerHealthBar::PlayerHealthBar()
{

}