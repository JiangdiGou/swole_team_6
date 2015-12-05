/******************************************************************************/
/*!
\file   Core.cpp
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
CoreEngine Functions and GameLoop behavior
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include <Windows.h>
#include "Core.h"
#include "engineGraphics/Graphics.h"
#include "Message.h"
#include "mouseVector.h"
#include "_EntryPoint.h"
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

    //FMSoundSys sound = *new FMSoundSys();
    ////sound.Initialize(); <-- deprecated

    //FMSound soundSample;
    //sound.createSound(&soundSample, "resources//audio//menutheme.wav");

    //// loop the sound
    //sound.playSound(soundSample, true);
	  SoundEmitter bgm = *new SoundEmitter();
	  bgm.Initialize();

	  bgm.SetVolume(1.0f, "demotitle2");
	  bgm.StopEvent("demotitle2");
	  bgm.PlayEvent("demotitle2");
	  
	  
  
#endif

  while (GameActive)
  {
    //updateMousePos();
    if (GameState == GS_LOAD)
	{
		if (PrevGameState == GS_RUN)
		{
		if (LevelName == "resources/Levels/WinScreen.txt")
		{
			SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));

			emitter->SetPause(true, "demotitle2");
		}
		FACTORY->destroyAllObjects();
		PHYSICS->Reload();
        LOGIC->createLevel(LevelName);
		if (LevelName == "resources/Levels/WinScreen.txt")
		{
			SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));

			emitter->SetVolume(1.0f, "Win");
			emitter->StopEvent("Win");
			emitter->PlayEvent("Win");
		}
		else if (LevelName == "resources/Levels/LoseScreen.txt")
		{
			SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));

			emitter->SetVolume(1.0f, "Death");
			emitter->StopEvent("Death");
			emitter->PlayEvent("Death");
		}
		else
		{
			SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));

			emitter->SetVolume(1.0f, "demotitle2");
			emitter->StopEvent("demotitle2");
			emitter->PlayEvent("demotitle2");
		}
        GameState = GS_RUN;
        //PHYSICS->Initialize();
        //for (unsigned i = 0; i < Systems.size(); ++i)
        //{
          //Systems[i]->Initialize();
        //}

      }
    }
    else if(GameState == GS_RUN)
    {
      unsigned currenttime = timeGetTime();
      //Convert it to the time passed since the last frame (in seconds)
      float dt = (currenttime - LastTime) / 1000.0f;
      //Update the when the last update started
      LastTime = currenttime;

      //if (!(CORE->Pause))
      //{
        //Update every system
      for (unsigned i = 0; i < Systems.size(); ++i)
      {
        if (CORE->Pause && (Systems[i] == PHYSICS || Systems[i] == sound))
          continue;
        else
          Systems[i]->Update(dt);
      }

      for (unsigned i = 0; i < Systems.size(); ++i)
        Systems[i]->Draw();
      //}
      //else
      //{
       // PAUSEMENU->Update(dt);
        //FACTORY->Update(dt);
        //GRAPHICS->Update(dt);
        //GRAPHICS->Draw();
      //}
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