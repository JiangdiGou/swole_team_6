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
  //std::cout << "----- FRAME END -----" << std::endl;

  while (deltaTime < frameTime)
    deltaTime = timeGetTime() - frameStartTime;

  dt = deltaTime;
  frameStartTime = timeGetTime();
}

