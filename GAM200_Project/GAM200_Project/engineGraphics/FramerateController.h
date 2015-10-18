#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

#define FRAMERATE 60.0

#include "Graphics.h"

//I think it's bad coding practice to have a static class but why 
//would we ever need multiple frame rate controllers and a class is
//just a nice way to group the data together 
class FramerateController
{
public: 
  static unsigned getPreviousDt();
  static void frameEnd();
 
private:
  static unsigned dt;
  static unsigned frameStartTime;
  //Returns how long the current frame has been going on, in ms
  static unsigned getCurrentFrameDuration();

};

#endif