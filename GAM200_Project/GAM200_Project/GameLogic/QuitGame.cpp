#include "QuitGame.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void QuitGame::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);
  
  pReactive = (GameReactive*)GetOwner()->has(GameReactive);
}

void QuitGame::Update(float dt)
{
	if (pReactive != nullptr)
	{
		if (pReactive->mouseDownAndOver())
		{
			std::cout << "Quit Game. DO IT NOW!!!";
			//CORE->GameActive = false;
			CORE->Pause = true;
			PAUSEMENU->state = AREYOUSURE;
		}
	}
}

void QuitGame::SendMessages(Message* message)
{
}

void QuitGame::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

QuitGame::QuitGame()
{

}