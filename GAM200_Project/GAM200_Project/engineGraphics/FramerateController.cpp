#include "FramerateController.h"
#include "Graphics.h"

unsigned FramerateController::frameStartTime = GetTickCount();
unsigned FramerateController::dt = 0;

float FramerateController::getCurrentFrameDuration()
{
  return GetTickCount() - frameStartTime;
}

float FramerateController::getPreviousDt()
{
  return dt;
}

void FramerateController::frameEnd()
{
  /* A lot of this function is commented out because I was trying to fix some 
   * weird behavior where we were getting 60 fps followed by 31, 31
   * Turns out, GetTickCount() only updates every 15 miliseconds. 
   * So, although our game calls GetTickCount() about 12 times every 15ms,
   * deltaTime only updates every 15 ms because GetTickCount is terrible apparently?
   * It's based on an interuppt or something. I dunno. Can look into tomorrow 
  */

  unsigned deltaTime = GetTickCount() - frameStartTime;
  unsigned frameTime = (unsigned)(1000.0f / FRAMERATE);

  std::cout << "Checking if...." << std::endl;
  std::cout << deltaTime << " < " << frameTime << std::endl;

  while (deltaTime < frameTime)
  {
    
    std::cout << "dt is less" << std::endl;
   std::cout << "Incremented from " << deltaTime << " to " << GetTickCount() - frameStartTime << std::endl;
    deltaTime = GetTickCount() - frameStartTime;
  }

  dt = deltaTime;
  std::cout << dt << std::endl;
  frameStartTime = GetTickCount();

  /*
 //If the frame took some percent longer than it should have 
  if (deltaTime > (unsigned)((1.0f + 0.01*FRWARNINGPERCENT)*(1000.0f / FRAMERATE)))
  {
    std::cout << "Warning, frame took " << dt << "ms and should have taken about ";
    std::cout << 1000.0f / FRAMERATE << "ms" << std::endl;
  }
  */
}

