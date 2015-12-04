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
	//GOC* enemy = parent->FindObject("Enemy1");
	//Transform* eTransform = enemy->has(Transform);

	//if ((pTransform->GetPositionX() - eTransform->GetPositionX()) < 1)
	//{
	//}

	if (!Alive)
	{
		CORE->LevelName = "resources/Levels/PlayerDeath.txt";

		CORE->GameState = GS_LOAD;
	}
}

void HealthManager::UpdateScale(float scale)
{
  //eTransform->SetScale(Vector3D((int)(CurrentHealth/TotalHealth), 1 , 1));
}

void HealthManager::UpdateHealth(int val)
{
	CurrentHealth += val;

  UpdateScale((float)(CurrentHealth / TotalHealth));

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