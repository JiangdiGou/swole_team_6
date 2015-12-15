/*****************************************************************************/
/*!
\file    FramerateController.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of the game's framerate controller, which locks the game's
  framerate at a particular value, found in init info
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "FramerateController.h"
#include "Graphics.h"
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
  unsigned frameTime = (unsigned)(1000.0f / 60.0f);

  timeBeginPeriod(1);

  while (deltaTime < frameTime)
    deltaTime = timeGetTime() - frameStartTime;

  dt = deltaTime;
  frameStartTime = timeGetTime();
}

