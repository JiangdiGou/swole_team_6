#ifndef MOUSEVECTOR_H
#define MOUSEVECTOR_H

#include "Component.h"
#include <utility>
#include <iostream>
#include "engineGraphics\Graphics.h"
#include "WindowsSystem.h"
#include "initInfo.h"

class mouseVector : public GameComponent
{
  glm::vec2 mouseDownPos;
  glm::vec2 mouseUpPos;

  void SendMessages(Message*) override;
  void Update(float dt) override {};
};


#endif