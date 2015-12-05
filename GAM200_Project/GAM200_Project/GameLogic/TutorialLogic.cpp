#include "TutorialLogic.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void TutorialLogic::Initialize()
{
  dist = 0;
	parent = GetOwner();
	pTransform = parent->has(Transform);

	pSprite = parent->has(Sprite);
  if (pSprite)
    pSprite->setLayer(1);

  ShapeAAB* pShape = parent->has(ShapeAAB);

  if (pShape != nullptr)
  {
    pShape->Extents.y = 10000;
  }

  delayTimer = 0.0f;

}

void TutorialLogic::Update(float dt)
{
  GOC* player = LOGIC->player;
  Transform* playerTransform = player->has(Transform);

  dist = pTransform->GetPositionX() - playerTransform->GetPositionX();
  
  if (dist < 0)
    dist *= -1;


  if (dist < 5)
    LoadNextLevel();
  /*
  if (delayTimer > 0)
  {
    delayTimer -= dt;
  }
  else if ((loadLevel) && (delayTimer <= 0))
  {
    LoadNextLevel();
  }
  */
}

void TutorialLogic::LoadNextLevel()
{
  if (parent->GetName() == "Sensei")
  {
    CORE->LevelName = "resources/Levels/Level1.txt";
    CORE->GameState = GS_LOAD;
  }
  else if (parent->GetName() == "NextLev")
  {
    CORE->LevelName = "resources/Levels/WinScreen.txt";
    CORE->GameState = GS_LOAD;
  }
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