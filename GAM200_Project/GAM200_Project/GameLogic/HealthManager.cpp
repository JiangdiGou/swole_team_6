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
	if (healthBar == NULL)
	{
		healthBar = parent->FindObject("HUDHealthBar");

		if (healthBar != NULL)
		{
			std::cout << "got here";
			healthBarComponent = healthBar->has(PlayerHealthBar);
		}
	}

	if (healthBarComponent != NULL)
	{
		
		healthBarComponent->UpdateScale(CurrentHealth / TotalHealth);
	}

	if (!Alive)
	{
		CORE->LevelName = "resources/Levels/PlayerDeath.txt";

		CORE->GameState = GS_LOAD;
	}
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