#include "FramerateController.h"
#include "Graphics.h"
#include <mmsystem.h>

unsigned FramerateController::frameStartTime = timeGetTime();
unsigned FramerateController::dt = 0;

unsigned FramerateController::getPreviousDt()
{
  return dt;
}
void FramerateController::frameEnd()
{
  unsigned deltaTime = timeGetTime() - frameStartTime;
  unsigned frameTime = (unsigned)(1000.0f / FRAMERATE);

  timeBeginPeriod(1);

  //std::cout << "Checking if...." << std::endl;
 // std::cout << deltaTime << " < " << frameTime << std::endl;

  while (deltaTime < frameTime)
  {
    
    //std::cout << "dt is less" << std::endl;
    //std::cout << "Incremented from " << deltaTime << " to " << timeGetTime() - frameStartTime << std::endl;
    deltaTime = timeGetTime() - frameStartTime;
  }

  dt = deltaTime;
  //std::cout << dt << std::endl;
  frameStartTime = timeGetTime();

  
  /*
 //If the frame took some percent longer than it should have 
  if (deltaTime > (unsigned)((1.0f + 0.01*FRWARNINGPERCENT)*(1000.0f / FRAMERATE)))
  {
    std::cout << "Warning, frame took " << dt << "ms and should have taken about ";
    std::cout << 1000.0f / FRAMERATE << "ms" << std::endl;
  }
  */
  
}

