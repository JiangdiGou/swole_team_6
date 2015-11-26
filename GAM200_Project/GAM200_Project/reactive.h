#ifndef REACTIVE_H
#define REACTIVE_H

#include "Component.h"
#include "WindowsSystem.h"
#include "physicsLib\Transform.h"
#include "engineGraphics\Sprite.h"

class Reactive : public GameComponent
{
public: 
  
  //Is this mouse over this object (based on transform)
  bool mouseOver() { return mouseIsOverThis;  }
  //Is object clicked basically 
  bool mouseDownAndOver() { return mouseDownOnThis; }
  //Is object clicked/held
  bool mouseDownHeldAndOver() { return mouseHeldOnThis;  }
  //Were the following modifier keys pressed?
  bool ctrlPressed() { return control;  }
  bool altPressed() { return alt;  }
  bool shiftPresed() { return shift;  }
  //Whats the current mouse pos?
  Vector2 getMousePos() { return mousePos; }

  //Call this in init
  bool fetchTransform();
  //Call this in update
  bool checkMouseHeld();
  //Call this in sendMessages
  void updateMouseFlags(Message* message);


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