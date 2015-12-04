#include "HealthManager.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void HealthManager::Initialize()
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

void HealthManager::Update(float dt)
{
	//UpdateScale((float)(CurrentHealth / TotalHealth));

	//GOC* enemy = parent->FindObject("Enemy1");
	//Transform* eTransform = enemy->has(Transform);

	//if ((pTransform->GetPositionX() - eTransform->GetPositionX()) < 1)
	//{
	//	std::cout << "im a genius?";
	//}

	if (!Alive)
	{
		CORE->LevelName = "resources/Levels/PlayerDeath.txt";

		CORE->GameState = GS_LOAD;
	}
}

void UpdateScale(float scale)
{
	std::cout << "im a genius?";
}

void HealthManager::UpdateHealth(int val)
{
	CurrentHealth += val;

	if (CurrentHealth <= 0)
	{
		Alive = false;
	}
}

void HealthManager::SendMessages(Message* message)
{
}

void HealthManager::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

HealthManager::HealthManager()
{

}