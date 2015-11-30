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
#include "GameLogic\PauseMenu.h"


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
        LOGIC->createLevel(LevelName);

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

      if (!Pause)
      {
        //Update every system
        for (unsigned i = 0; i < Systems.size(); ++i)
          Systems[i]->Update(dt);

        for (unsigned i = 0; i < Systems.size(); ++i)
          Systems[i]->Draw();
      }
      else
      {
        FACTORY->Update(0.016);
        GRAPHICS->Update(0.016);
        PAUSEMENU->Update(0.016);
        GRAPHICS->Draw();
      }
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