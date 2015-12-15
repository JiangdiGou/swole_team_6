/******************************************************************************/
/*!
\author Josh Painter

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "EnemyHealthManager.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void EnemyHealthManager::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  CurrentHealth = TotalHealth;
}

void EnemyHealthManager::Update(float dt)
{
	if (!Alive)
	{
    std::cout << "enemy died \n";

    parent->Destroy();
	}
}

void EnemyHealthManager::UpdateHealth(int val)
{
	CurrentHealth += val;

  std::cout << CurrentHealth << "\n";

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