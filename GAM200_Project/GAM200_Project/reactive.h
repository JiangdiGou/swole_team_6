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
  bool mouseOver() { return mouseIsOverThis;  }
  bool mouseDownAndOver() { return mouseDownOnThis; }
  bool mouseDownHeldAndOver() { return mouseHeldOnThis;  }
  bool ctrlPressed() { return control;  }
  bool altPressed() { return alt;  }
  bool shiftPresed() { return shift;  }
  Vector2 getMousePos() { return mousePos; }

private:
  Vector2 mousePos;
  bool mouseDownOnThis = false;
  bool mouseIsOverThis = false;
  bool mouseHeldOnThis = false;

  bool control;
  bool alt;
  bool shift;

  int mouseHoldCounter = 0;

  Transform* ownerTransform; 
};

#endif