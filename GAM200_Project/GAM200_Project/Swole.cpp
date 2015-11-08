/*****************************************************************************/
/*!
\file    Swole.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of Swole, which is mainly a wrapper storing core engine
  functionality
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "Swole.h"

Swole::Swole(const CoreEngine& engine) :logger(txtlog(SWOLELOG_FILENAME))
{
  for (std::vector<ISystem*>::iterator it = engine.getSystems().begin();
    it != engine.getSystems().end(); ++it)
  {
    systems.push_back(*it);
  }
}
