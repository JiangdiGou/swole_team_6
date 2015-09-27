///////////////////////////////////////////////////////////////////////////////////////
//
//	Core.cpp
//	Authors: Chris Peters
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include "Core.h"

//A global pointer to the core
CoreEngine* CORE;

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
    Systems[i]->Initialize();
}

void CoreEngine::GameLoop()
{
  LastTime = timeGetTime();

  while (GameActive)
  {
    unsigned currenttime = timeGetTime();
    //Convert it to the time passed since the last frame (in seconds)
    float dt = (currenttime - LastTime) / 1000.0f;
    //Update the when the last update started
    LastTime = currenttime;

    //Update every system
    for (unsigned i = 0; i < Systems.size(); ++i)
      Systems[i]->Update(dt);
  }

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