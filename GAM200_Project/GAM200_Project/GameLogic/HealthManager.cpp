#include "HealthManager.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void HealthManager::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);

	player = LOGIC->player;

  //healthBar = "TempHealthBar");
  //healthBarComponent = healthBar->has(PlayerHealthBar);

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
	GOC* owner = GetOwner();

	if (!Alive)
	{
		CORE->LevelName = "resources/Levels/PlayerDeath.txt";

		CORE->GameState = GS_LOAD;
	}
}

void HealthManager::UpdateHealth(int val)
{
	CurrentHealth += val;

  //healthBarComponent->UpdateScale(CurrentHealth / TotalHealth);

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