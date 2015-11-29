#include "PauseMenu.h"

void PauseMenu::Initialize()
{
  GOC* resumeButton = FACTORY->makeObject("Resume");
  pauseMenuObjects.push_back(resumeButton); 
  GOC* h2playButton = FACTORY->makeObject("HowToPlay");
  pauseMenuObjects.push_back(h2playButton);
  GOC* quitButton = FACTORY->makeObject("Quit");
  pauseMenuObjects.push_back(quitButton);

}

void PauseMenu::Update(float dt)
{
  if (!CORE->Pause)
  {
    for (std::vector<GOC*>::iterator it = pauseMenuObjects.begin();
      it != pauseMenuObjects.end(); ++it)
    {
      Sprite* pSprite = (*it)->has(Sprite);

      if (pSprite && pSprite->visible)
        pSprite->visible = false;
    }
  }
  else
  {
    for (std::vector<GOC*>::iterator it = pauseMenuObjects.begin();
      it != pauseMenuObjects.end(); ++it)
    {
      Sprite* pSprite = (*it)->has(Sprite);

      if (pSprite && !(pSprite->visible))
        pSprite->visible = true;
    }
  }
}

void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset)
{
  Transform* pTransform = follower->has(Transform); 
  Vector2 newTransform = pTransform->GetPositionXY() + offset;

  pTransform->SetPosition(Vector3(newTransform, 0.25));
}

void PauseMenu::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::CharacterKey:
  {
    MessageCharacterKey* charMsg = (MessageCharacterKey*)message;
    if (charMsg->character == 'P')
    {
      CORE->Pause = true;
    }
  }
  }
}
