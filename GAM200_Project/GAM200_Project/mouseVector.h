#ifndef MOUSEVECTOR_H
#define MOUSEVECTOR_H

#include "Component.h"
#include <utility>
#include <iostream>
#include "engineGraphics\Graphics.h"
#include "WindowsSystem.h"
#include "initInfo.h"
#include "GameLogic.h"
#include "physicsLib\Transform.h"
#include "engineGraphics\debugDraw.h"

class mouseVector : public GameComponent
{
  Vector2 mouseDownPos;
  Vector2 mouseUpPos;

  bool mouseDown;

  void SendMessages(Message*) override;
  void Update(float dt) override;
};


#endif