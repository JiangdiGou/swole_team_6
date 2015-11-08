/*****************************************************************************/
/*!
\file    Swole.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of Swole, which is just a wrapper for core engine functioanlity
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef SWOLE_H
#define SWOLE_H

#include "Core.h"
#include "logger\logger.h"
#include <vector>

#define SWOLELOG_FILENAME "swoleLog.txt"

class Swole
{
  Swole(const CoreEngine& engine);

  virtual void SendMessages(Message *) {};

  txtlog logger;
  std::vector<ISystem*> systems = {};
};

#endif
