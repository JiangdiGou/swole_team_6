/******************************************************************************/
/*!
\file   Message.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
  ISystem Derived Class declarations
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef SYSTEM_H
#define SYSTEM_H
#include "Message.h"

class ISystem
{
public:
  virtual void SendMessages(Message* message) {};
  ///All systems are updated every game frame.
  virtual void Update(float dt) = 0;

  ///Initialize the system.
  virtual void Initialize() {};
  ///Initialize the system.
  virtual void Draw() {};

  ///All systems need a virtual destructor to have their destructor called 
  virtual ~ISystem() {}
};
#endif