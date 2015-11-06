/*****************************************************************************/
/*!
\file       FramerateController.cpp
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     Implementation of our game's frame rate controller
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#include "FramerateController.h"
#include "Graphics.h"
#include "../initInfo.h"
#include <mmsystem.h>

//initInfo * INITINFO;

unsigned FramerateController::frameStartTime = timeGetTime();
unsigned FramerateController::dt = 0;

unsigned FramerateController::getPreviousDt()
{
  return dt;
}
void FramerateController::frameEnd()
{
  unsigned deltaTime = timeGetTime() - frameStartTime;
  unsigned frameTime = (unsigned)(1000.0f / INITINFO->FPSlimit);

  timeBeginPeriod(1);

  while (deltaTime < frameTime)
    deltaTime = timeGetTime() - frameStartTime;

  dt = deltaTime;
  frameStartTime = timeGetTime();
}

