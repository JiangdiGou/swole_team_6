#ifndef EDITABLE_H
#define EDITABLE_H

//This is the interface  for the editor into components.

#include "../Component.h"
#include "../reactive.h"
#include "imGuiManager.h"

class Editable : public GameComponent
{
public:
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

private:
  Reactive* pReactive = 0;
  GameObjectComposition* parent = 0;
};

#endif