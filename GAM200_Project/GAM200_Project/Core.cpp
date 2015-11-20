///////////////////////////////////////////////////////////////////////////////////////
//
//	Core.cpp
//	Authors: Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "Core.h"
#include "engineGraphics/Graphics.h"
#include "Message.h"
#include "mouseVector.h"
#include "_EntryPoint.h"
#include "initinfo.h"
#include "physicsLib\PlayerState.h"
#include "engineAudio/Audio.h"


CoreEngine* CORE = NULL;

CoreEngine::CoreEngine()
{
  LastTime = 0;
  GameActive = true;
  CORE = this; //Set the global pointer
}

CoreEngine::~CoreEngine()
{
}

void CoreEngine::Initialize()
{
  for (unsigned i = 0; i < Systems.size(); ++i)
	  Systems[i]->Initialize();/* so which system !? */
}

void CoreEngine::GameLoop()
{
  LastTime = timeGetTime();

#ifdef AUDIO_AT_PRESENTATION
  //std::string garbage;
  //FMSoundSys sound = *new FMSoundSys();
  ////sound.Initialize(); <-- deprecated

  //FMSound soundSample;
  //sound.createSound(&soundSample, "resources//audio//menutheme.wav");

  //// loop the sound
  //sound.playSound(soundSample, true);
  //std::cin >> garbage;
  //sound.releaseSound(soundSample);
  SoundEmiiter bgm = *new SoundEmitter();
  bgm.SetVolume(1.0f, "Combat_Music");
  bgm.PlayEvent("Combat_Music");
#else




  
 
 

  if (INITINFO->playTheme)
  {
    //FMSoundSys sound = *new FMSoundSys();
    ////sound.Initialize(); <-- deprecated

    //FMSound soundSample;
    //sound.createSound(&soundSample, "resources//audio//menutheme.wav");

    //// loop the sound
    //sound.playSound(soundSample, true);
	  SoundEmitter bgm = *new SoundEmitter();
	  bgm.Initialize();

	  bgm.SetVolume(1.0f, "PartyCrashv3");
	  bgm.StopEvent("PartyCrashv3");
	  bgm.PlayEvent("PartyCrashv3");
	  
	  
  }
#endif

  while (GameActive)
  {
    //updateMousePos();
    if (GameState == GS_LOAD)
    {
      if (PrevGameState == GS_RUN)
      {
        FACTORY->destroyAllObjects();
        FACTORY->textureKey = FACTORY->readTextureKey(this->textureKeyFile);
        //FACTORY->loadLevelFrom("resources/Levels/InGameEditor.txt");
        FACTORY->loadLevelFrom(LevelName);

        FACTORY->createTiles();

        GOC * camera = FACTORY->makeObject("Camera");
        camera->AddComponent(CT_Transform, new Transform());
        Camera *mainCamera = new Camera(*(GRAPHICS->getCoreShader()));
        mouseVector *vectTest = new mouseVector();
        camera->AddComponent(CT_MouseVector, vectTest);
        camera->AddComponent(CT_Camera, mainCamera);
#ifdef EDITOR
        mainCamera->followingPlayer = false;
        mainCamera->editorMode = true;
#endif
        camera->Initialize();


        //PLAYER
        GOC * player = FACTORY->makeObject("player");
        Transform * transformPlayer = new Transform();
        transformPlayer->SetPosition(2, 6, 0);
        transformPlayer->SetScale(Vector2(1.25, 1.25));
        player->AddComponent(CT_Transform, transformPlayer);

#ifdef EDITOR
        Reactive* playerReactive = new Reactive();
        player->AddComponent(CT_Reactive, playerReactive);
        Editable* editable = new Editable(false);
        player->AddComponent(CT_Editable, editable);
#endif

        Body * bodyPlayer = new Body();
        bodyPlayer->Mass = 3.0f;
        bodyPlayer->Restitution = 0.3f;
        bodyPlayer->Friction = 0.0f;
        ShapeAAB * boxColliderPlayer = new ShapeAAB();
        boxColliderPlayer->Extents = Vec2D(0.5 * transformPlayer->GetScale().x, 0.5 * transformPlayer->GetScale().y);
        bodyPlayer->BodyShape = boxColliderPlayer;



        player->AddComponent(CT_Body, bodyPlayer);
        player->AddComponent(CT_ShapeAAB, boxColliderPlayer);
        PlayerState * controller = new PlayerState();
        player->AddComponent(CT_PlayerState, controller);

        SoundEmitter* playerSound = new SoundEmitter();
        player->AddComponent(CT_SoundEmitter, playerSound);

        //TileMapCollision * tileplayer = new TileMapCollision();
        //player->AddComponent(CT_TileMapCollision, tileplayer);


        Sprite * spritePlayer = new Sprite();
        spritePlayer->texture = GRAPHICS->getSpriteAtlas()->textures["Character"];
        spritePlayer->flipSprite = false;
        player->AddComponent(CT_Sprite, spritePlayer);

        LOGIC->player = player;

        GRAPHICS->setMainCamera(mainCamera);
        FACTORY->initializeObjects();
        //LOGIC->Initialize();
        GameState = GS_RUN;
      }
    }
    else if(GameState == GS_RUN)
    {
      unsigned currenttime = timeGetTime();
      //Convert it to the time passed since the last frame (in seconds)
      float dt = (currenttime - LastTime) / 1000.0f;
      //Update the when the last update started
      LastTime = currenttime;

      //Update every system
      for (unsigned i = 0; i < Systems.size(); ++i)
        Systems[i]->Update(dt);

      for (unsigned i = 0; i < Systems.size(); ++i)
        Systems[i]->Draw();
    }
  }

}

void CoreEngine::BroadcastMessage(Message* message)
{
  //The message that tells the game to quit
  if (message->MessageId == Mid::Quit)
    GameActive = false;

  //Send the message to every system--each
  //system can figure out whether it cares
  //about a given message or not
  for (unsigned i = 0; i < Systems.size(); ++i)
    Systems[i]->SendMessages(message);
}
void CoreEngine::AddSystem(ISystem* system)
{
  Systems.push_back(system);
}

void CoreEngine::DestroySystems()
{
  for (unsigned i = 0; i < Systems.size(); i++)
  {
    delete Systems[Systems.size() - i - 1];
  }
}