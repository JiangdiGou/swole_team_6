#ifndef GAMEREACTIVE_H
#define GAMEREACTIVE_H

//This is the interface  for the editor into components.

#include "../Component.h"
#include "../reactive.h"
#include "../Zilch/BindInternal.hpp"
#include "../Zilch/Zilch.hpp"

using namespace Zilch;

class GameReactive : public Reactive
{
public:
  ZilchDeclareDerivedType(GameReactive, Reactive);
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

  void SerializeWrite(Serializer& str);


private:
  int stuff;

};

#endif