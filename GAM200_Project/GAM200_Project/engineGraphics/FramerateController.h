/*****************************************************************************/
/*!
\file    FramerateController.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of the game's framerate controller, which locks the game's
  framerate at particular value, found in init info
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

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
