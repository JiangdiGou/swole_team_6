#ifndef ZILCHCOMPONENT_H
#define ZILCHCOMPONENT_H
#include "Component.h"
#include "Zilch\ZilchInterface.hpp"
#include "Zilch\ZilchManager.h"
#include "Zilch\Zilch.hpp"
#include <string.h>

using namespace Zilch;

class OurZilchComponent : public GameComponent 
{
public:
  ZilchDeclareDerivedType(OurZilchComponent, GameComponent);
  OurZilchComponent(std::string scriptName, ZilchComponentTypeId zilchId);
  ~OurZilchComponent();
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

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


#endif