/******************************************************************************/
/*!
\file   ZilchComponent.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
  Declarations of ZilchComponent Function Pointers
All content � 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef ZILCHCOMPONENT_H
#define ZILCHCOMPONENT_H
#include "Component.h"
#include "Zilch\ZilchInterface.hpp"
#include "Zilch\ZilchManager.h"
#include "Zilch\Zilch.hpp"
#include "Zilch\BindInternal.hpp"
#include <string.h>

using namespace Zilch;

class OurZilchComponent : public GameComponent 
{
public:
  ZilchDeclareDerivedType(OurZilchComponent, GameComponent);
  OurZilchComponent() : classScript("Example"), zilchId(CTZ_Example) {};
  OurZilchComponent(std::string scriptName, ZilchComponentTypeId zilchId);
  ~OurZilchComponent();
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;
  void CallFunction(std::string);
  Function* GetFieldOrProperty(std::string functName);
  Function* SetFieldOrProperty(std::string functName);
  ExceptionReport report;
  BoundType* zilchClass;
  Handle classInstance;
  std::string classScript;
  ZilchComponentTypeId zilchId;
  Function* initFunc;
  Function* updateFunc;
  Function* OnCollideStart;
  Function* OnCollidePersist;
  Function* OnCollideEnd;
  Function* OnCustomEvent;
  Function* OnKeyboardDown;
  Function* OnMouseLeftDown;
  Function* OnMouseRightDown;
  Function* OnMouseLeftUp;
  Function* OnMouseRightUp;
  Function* OnMouseMove;
  Function* Destroy;
};

#define createZilch(arg) OurZilchComponent(#arg, CTZ_##arg);

#endif