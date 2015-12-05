#include "WinLogic.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void WinLogic::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  numEnemies = 0;
  totalEnemies = 0;

  KillCounterPlus();
}

void WinLogic::Update(float dt)
{
	
}

void WinLogic::SendMessages(Message* message)
{
}

void WinLogic::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

void WinLogic::KillCounterPlus()
{
	numEnemies++;

	if (numEnemies >= totalEnemies)
	{
		CORE->LevelName = "resources/Levels/WinScreen.txt";
		std::cout << "All dem peepelz be dead";
		CORE->GameState = GS_LOAD;
	}

}

WinLogic::WinLogic()
{

}