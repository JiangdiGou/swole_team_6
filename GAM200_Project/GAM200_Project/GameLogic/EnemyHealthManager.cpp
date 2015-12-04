#include "EnemyHealthManager.h"
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

  CurrentHealth = TotalHealth;

#ifdef EDITOR
  //CanMove = false;
#else
  //CanMove = true;
#endif
}

void EnemyHealthManager::Update(float dt)
{
	if (!Alive)
	{
    parent->Destroy();
	}
}

void EnemyHealthManager::UpdateHealth(int val)
{
	CurrentHealth += val;

	if (CurrentHealth <= 0)
	{
		Alive = false;
	}
}

void EnemyHealthManager::SendMessages(Message* message)
{
  //switch (message->MessageId)
  //{
  //case Mid::CharacterKey:
  //    MessageCharacterKey* charMessage = (MessageCharacterKey*)message;
  //    switch(charMessage->character)
  //      case '2':
  //        if (IsAltHeld() && IsCtrlHeld())
  //        {
  //          GodMode = true;
  //        }
  //        break;
  //      case '.':
  //        if (IsAltHeld() && IsCtrlHeld())
  //        {
  //          GodMode = false;
  //        }
  //        break;
  //    break;
  //}
}

void EnemyHealthManager::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

EnemyHealthManager::EnemyHealthManager()
{

}