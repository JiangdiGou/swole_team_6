/******************************************************************************/
/*!
\author Mitch Regan

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "LoadLevel.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void LoadLevel::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);
  
  pReactive = (GameReactive*)GetOwner()->has(GameReactive);
}

void LoadLevel::Update(float dt)
{
	if (pReactive != nullptr)
	{
		if (pReactive->mouseDownAndOver())
		{
			CORE->LevelName = "resources/Levels/Level1.txt";

			CORE->GameState = GS_LOAD;
		}
	}
}

void LoadLevel::SendMessages(Message* message)
{
}

void LoadLevel::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

LoadLevel::LoadLevel()
{

}