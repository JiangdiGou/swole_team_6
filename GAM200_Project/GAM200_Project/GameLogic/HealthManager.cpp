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
  pHealthBar = FACTORY->FindObjectByName("HUDHealthBar ");

  CurrentHealth = TotalHealth;
#ifdef EDITOR
  //CanMove = false;
#else
  //CanMove = true;
#endif
}

void HealthManager::Update(float dt)
{
  if (GodMode == true)
  {
    CurrentHealth = TotalHealth;
  }
	if (!Alive)
	{
		CORE->LevelName = "resources/Levels/PlayerDeath.txt";

		CORE->GameState = GS_LOAD;
	}
}

void HealthManager::UpdateHealth(int val)
{
  if (GodMode == true)
  {
    return;
  }
	CurrentHealth += val;
  PlayerHealthBar* healthBar = pHealthBar->has(PlayerHealthBar);
  healthBar->UpdateScale( (float)(CurrentHealth) / (float)(TotalHealth) );
  std::cout << "Player Health:" << CurrentHealth << ", Total Health: " << TotalHealth << "\n";
	if (CurrentHealth <= 0)
	{
		Alive = false;
	}
}

void HealthManager::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::CharacterKey:
      MessageCharacterKey* charMessage = (MessageCharacterKey*)message;

	  switch (charMessage->character)
	  {
	  case '2':
		  if (IsAltHeld() && IsCtrlHeld())
		  {
			  GodMode = true;
		  }
		  break;
	  case '.':
		  if (IsAltHeld() && IsCtrlHeld())
		  {
			  GodMode = false;
		  }
		  break;
	  default:
		  break;
	  }
      break;
  }
}

void HealthManager::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

HealthManager::HealthManager()
{

}