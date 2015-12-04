#include "PauseMenu.h"
#include "../engineAudio/SoundEmitter.h"

PauseMenu* PAUSEMENU;

PauseMenu::PauseMenu()
{
  PAUSEMENU = this;
}

void PauseMenu::Initialize()
{
  //MAIN MENU
  //RESUME
	
  GOC* resumeButton = FACTORY->makeMenuObject("Resume");
  //Components
  Transform* pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  Sprite* pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["ResumeGame"];
  GameReactive* pReactive = new GameReactive();
  pReactive->active = false;
  MenuButton* pButton = new MenuButton(RESUME);
  //Add
  resumeButton->AddComponent(CT_Transform, pTrasnform);
  resumeButton->AddComponent(CT_Sprite, pSprite);
  resumeButton->AddComponent(CT_GameReactive, pReactive);
  resumeButton->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(resumeButton); 

  //HOW TO PLAY
  GOC* h2playButton = FACTORY->makeMenuObject("HowToPlay");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["HowToPlay"];
  pReactive = new GameReactive();
  pReactive->active = false;
  //Add
  pButton = new MenuButton(HOWTOPLAY);
  h2playButton->AddComponent(CT_Transform, pTrasnform);
  h2playButton->AddComponent(CT_Sprite, pSprite);
  h2playButton->AddComponent(CT_GameReactive, pReactive);
  h2playButton->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(h2playButton);

  //QUIT
  GOC* quitButton = FACTORY->makeMenuObject("Quit");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["QuitGame"];
  pReactive = new GameReactive();
  pReactive->active = false;
  pButton = new MenuButton(QUIT);
  //Add
  quitButton->AddComponent(CT_Transform, pTrasnform);
  quitButton->AddComponent(CT_Sprite, pSprite);
  quitButton->AddComponent(CT_GameReactive, pReactive);
  quitButton->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(quitButton);

  //QUIT VERIFICATION
  //This is not a button
  GOC* areYouSure = FACTORY->makeMenuObject("AreYouSure");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["AreYouSure"];
  pReactive = new GameReactive();
  pReactive->active = false;
  pButton = new MenuButton(AREYOUSURESPRITE);
  //Add
  areYouSure->AddComponent(CT_Transform, pTrasnform);
  areYouSure->AddComponent(CT_Sprite, pSprite);
  areYouSure->AddComponent(CT_GameReactive, pReactive);
  areYouSure->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(areYouSure);

  //IAMSURE
  //QUIT
  GOC* iAmSure = FACTORY->makeMenuObject("IAmSure");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["Yes"];
  pReactive = new GameReactive();
  pReactive->active = false;
  pButton = new MenuButton(IAMSURE);
  //Add
  iAmSure->AddComponent(CT_Transform, pTrasnform);
  iAmSure->AddComponent(CT_Sprite, pSprite);
  iAmSure->AddComponent(CT_GameReactive, pReactive);
  iAmSure->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(iAmSure);


  //IAMNOTSURE
  GOC* iAmNotSure = FACTORY->makeMenuObject("IAmNotSure");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["No"];
  pReactive = new GameReactive();
  pButton = new MenuButton(IAMNOTSURE);
  //Add
  iAmNotSure->AddComponent(CT_Transform, pTrasnform);
  iAmNotSure->AddComponent(CT_Sprite, pSprite);
  iAmNotSure->AddComponent(CT_GameReactive, pReactive);
  iAmNotSure->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(iAmNotSure);

  //HOWTOPLAYSCREEN
  //HOWTOPLAYSPRITE
  GOC* howToPlaySprite = FACTORY->makeMenuObject("HowToPlaySprite");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(12, 9));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["Instructions"];
  pReactive = new GameReactive();
  pButton = new MenuButton(HOWTOPLAYSPRITE);
  //Add
  howToPlaySprite->AddComponent(CT_Transform, pTrasnform);
  howToPlaySprite->AddComponent(CT_Sprite, pSprite);
  howToPlaySprite->AddComponent(CT_GameReactive, pReactive);
  howToPlaySprite->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(howToPlaySprite);

  //GOBACK
  GOC* goBack = FACTORY->makeMenuObject("GoBack");
  //Components
  pTrasnform = new Transform();
  pTrasnform->SetScale(Vector2(4, 2));
  pSprite = new Sprite();
  pSprite->texture = GRAPHICS->getSpriteAtlas()->textures["Back"];
  pReactive = new GameReactive();
  pButton = new MenuButton(GOBACK);
  //Add
  goBack->AddComponent(CT_Transform, pTrasnform);
  goBack->AddComponent(CT_Sprite, pSprite);
  goBack->AddComponent(CT_GameReactive, pReactive);
  goBack->AddComponent(CT_MenuButton, pButton);
  pauseMenuObjects.push_back(goBack);

  resumeButton->Initialize();
  h2playButton->Initialize();
  quitButton->Initialize();
  areYouSure->Initialize();
  iAmSure->Initialize();
  iAmNotSure->Initialize();
  howToPlaySprite->Initialize();
  goBack->Initialize();
}

void PauseMenu::Update(float dt)
{
  if (!(CORE->Pause))
  {
    //SoundEmitter* emitter = (SoundEmitter*)LOGIC->player->GetComponent(CT_SoundEmitter);
    //emitter->Rock();


    for (std::vector<GOC*>::iterator it = pauseMenuObjects.begin();
      it != pauseMenuObjects.end(); ++it)
    {
      Sprite* pSprite = (*it)->has(Sprite);
      GameReactive* pReactive = (*it)->has(GameReactive);

      if (pSprite && pSprite->visible)
        pSprite->visible = false;

      if (pReactive && pReactive->active)
        pReactive->active = false;

    }
  }
  else
  {
    
	 // pSound->BeQuiet();
    for (std::vector<GOC*>::iterator it = pauseMenuObjects.begin();
      it != pauseMenuObjects.end(); ++it)
    {
      Sprite* pSprite = (*it)->has(Sprite);
      GameReactive* pReactive = (*it)->has(GameReactive);
      MenuButton* pMenuButton = (*it)->has(MenuButton);
      
      if (!pMenuButton)
        return;

      switch (state)
      {
        //If we're in the main menu
      case MAINMENU:
      {
        //And youre one of the menu buttons in the main menu
        if (pMenuButton->type == HOWTOPLAY || pMenuButton->type == RESUME
          || pMenuButton->type == QUIT)
        {
          //Activate
          if (pSprite)
            pSprite->visible = true;

          if (pReactive)
            pReactive->active = true;

          switch (pMenuButton->type)
          {
          case HOWTOPLAY:
          {
            followCameraWithOffset(*it, Vector2(0, 0));
            break;
          }
          case RESUME:
          {
            followCameraWithOffset(*it, Vector2(0, 3));
            break;
          }
          case QUIT:
          {
            followCameraWithOffset(*it, Vector2(0, -3));
            break;
          }
          }
        }
          //If youre not in the main menu, disbale
        else
        {
          if (pSprite)
            pSprite->visible = false;

          if (pReactive)
            pReactive->active = false;
        }
        break;
      }
      case AREYOUSURE:
      {
		  SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		  emitter->SetVolume(1.0f, "Enter");
		  
		  emitter->PlayEvent("Enter");
		  emitter->StopEvent("Enter");
        //And youre one of the menu buttons in the main menu
        if (pMenuButton->type == IAMSURE || pMenuButton->type == IAMNOTSURE
          || pMenuButton->type == AREYOUSURESPRITE)
        {
          //Activate
          if (pSprite)
            pSprite->visible = true;

          if (pReactive)
            pReactive->active = true;

          switch (pMenuButton->type)
          {
          case IAMSURE:
          {
            followCameraWithOffset(*it, Vector2(4, -1));
            break;
          }
          case IAMNOTSURE:
          {
            followCameraWithOffset(*it, Vector2(-4, -1));
            break;
          }
          case AREYOUSURESPRITE:
          {
            followCameraWithOffset(*it, Vector2(0, 2));
            break;
          }
          }
        }
        //If youre not in the quit verification, disbale
        else
        {
          if (pSprite)
            pSprite->visible = false;

          if (pReactive)
            pReactive->active = false;
        }
      break;
      }
      case INSTRUCTIONS:
      {
        //And youre one of the menu buttons in the main menu
        if (pMenuButton->type == HOWTOPLAYSPRITE || pMenuButton->type == GOBACK)
        {
          //Activate
          if (pSprite)
            pSprite->visible = true;

          if (pReactive)
            pReactive->active = true;

          switch (pMenuButton->type)
          {
          case HOWTOPLAYSPRITE:
          {
            followCameraWithOffset(*it, Vector2(0, 2));
            break;
          }
          case GOBACK:
          {
            followCameraWithOffset(*it, Vector2(0, -5));
            break;
          }

          }
        }
        //If youre not in the quit verification, disbale
        else
        {
          if (pSprite)
            pSprite->visible = false;

          if (pReactive)
            pReactive->active = false;
        }
        break;
      }
      }
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
    //'\0' is escape apparently.
    if (charMsg->character == '\0' && charMsg->keyStatus == KEY_PRESSED)
    {
		 
		SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		emitter->StopEvent("Enter");
		emitter->PlayEvent("Enter");
	
		//pSound->BeQuiet();
      if (CORE->Pause)
      {	 
		  SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		  emitter->Rock();
		 
        GRAPHICS->toggleBackground(true);
        state = MAINMENU;
      }
	  else
	  {
		  SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		  emitter->BeQuiet();
		  GRAPHICS->toggleBackground(false);
	  }
      CORE->Pause = !CORE->Pause;
    }
  }
  }
}