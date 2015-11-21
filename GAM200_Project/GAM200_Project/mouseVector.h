/*****************************************************************************/
/*!
\file    mouseVector.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of mousevector, which stores mouse up and down event information.
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef MOUSEVECTOR_H
#define MOUSEVECTOR_H

#include "Component.h"
#include <utility>
#include <iostream>
#include "engineGraphics\Graphics.h"
#include "engineGraphics\graphicsManager.h"
#include "WindowsSystem.h"
#include "initInfo.h"
#include "GameLogic\GameLogic.h"
#include "physicsLib\Transform.h"
#include "engineGraphics\debugDraw.h"
#include "Composition.h"
//#include "physicsLib/RayLineBoxCollision.h"

class MouseVector : public GameComponent
{
public:
  Vector2 mouseDownPos;
  Vector2 mouseUpPos;
  
  
  bool mouseDown;

  void SendMessages(Message*) override;
  void Update(float dt) override;
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

 private:
	//SoundEmitter  mouseSound = *new SoundEmitter();
  GameObjectComposition* parent;
};


#endif
