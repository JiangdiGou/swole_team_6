#ifndef REACTIVE_H
#define REACTIVE_H

#include "Component.h"
#include "WindowsSystem.h"
#include "physicsLib\Transform.h"
#include "engineGraphics\Sprite.h"

class Reactive : public GameComponent
{
public: 
  void Initialize(); 
  void Update(float dt);
  void SendMessages(Message*) override;
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;
  bool mouseOver();

private:
  bool mouseDown = false;
  bool mouseIsOver = false;
  Transform* ownerTransform;
};

#endif