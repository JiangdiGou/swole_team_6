#include "TutorialLogic.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void TutorialLogic::Initialize()
{
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  delayTimer = 0.0f;

}

void TutorialLogic::Update(float dt)
{
  if (delayTimer > 0)
  {
    delayTimer -= dt;
  }
  else if ((loadLevel) && (delayTimer <= 0))
  {
    LoadNextLevel();
  }

}

void TutorialLogic::LoadNextLevel()
{
  CORE->LevelName = "resources/Levels/Level1.txt";
  std::cout << "Loading Level 1...";
  CORE->GameState = GS_LOAD;
}

void TutorialLogic::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
    case Mid::CollisionStarted:
    {
      CollisionStarted* CollisionMsg = (CollisionStarted*)message;
      GOC* other = CollisionMsg->otherObj->GetOwner();

      if (other->GetName() == "GAMEPLAYER")
      {
        std::cout << "Collided: Loading Level...";

        loadLevel = true;
        delayTimer = 1.0f;
      }
    }
  }
}

void TutorialLogic::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

TutorialLogic::TutorialLogic()
{

}