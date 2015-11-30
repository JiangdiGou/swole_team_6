#include "PauseMenu.h"

PauseMenu* PAUSEMENU;

PauseMenu::PauseMenu()
{
  PAUSEMENU = this;
}

void PauseMenu::Initialize()
{
  GOC* resumeButton = FACTORY->makeMenuObject("Resume");
  Transform* pTrasnform = new Transform();
  Sprite* pSprite = new Sprite();
  GameReactive* pReactive = new GameReactive();
  TestComponent* pTestComp = new TestComponent();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["StartGame"];
  resumeButton->AddComponent(CT_Transform, pTrasnform);
  resumeButton->AddComponent(CT_Sprite, pSprite);
  resumeButton->AddComponent(CT_GameReactive, pReactive);
  resumeButton->AddComponent(CT_TestComponent, pTestComp);

  MenuButton* pButton = new MenuButton(RESUME);
  resumeButton->AddComponent(CT_MenuButton, pButton);

  pauseMenuObjects.push_back(resumeButton); 

  GOC* h2playButton = FACTORY->makeMenuObject("HowToPlay");
  pTrasnform = new Transform();
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["StartGame"];
  h2playButton->AddComponent(CT_Transform, pTrasnform);
  h2playButton->AddComponent(CT_Sprite, pSprite);
  pauseMenuObjects.push_back(h2playButton);

  GOC* quitButton = FACTORY->makeMenuObject("Quit");
  pTrasnform = new Transform();
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["StartGame"];
  quitButton->AddComponent(CT_Transform, pTrasnform);
  quitButton->AddComponent(CT_Sprite, pSprite);
  pauseMenuObjects.push_back(quitButton);

  resumeButton->Initialize();
  h2playButton->Initialize();
  quitButton->Initialize();
}

void PauseMenu::Update(float dt)
{
  if (!(CORE->Pause))
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

      followCameraWithOffset(*it, Vector2(0, 2 - 2*(it - pauseMenuObjects.begin())));
    }
  }
}

void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset)
{
  Transform* pTransform = follower->has(Transform); 
  Vector2 cameraPos = Vector2(GRAPHICS->getCamera()->getPosition().x, GRAPHICS->getCamera()->getPosition().y);
  Vector2 newTransform = cameraPos + offset;

  if (pTransform)
    pTransform->SetPosition(Vector3(newTransform, 0.25));
}

void PauseMenu::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::CharacterKey:
  {
    MessageCharacterKey* charMsg = (MessageCharacterKey*)message;
    if (charMsg->character == 'P' && charMsg->keyStatus == KEY_PRESSED)
    {
      CORE->Pause = !CORE->Pause;
    }
  }
  }
}
