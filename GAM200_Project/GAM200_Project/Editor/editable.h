#ifndef EDITABLE_H
#define EDITABLE_H

//This is the interface  for the editor into components.

#include "../Component.h"
#include "../reactive.h"
#include "imGuiManager.h"

class Editable : public GameComponent
{
public:
  Editable(bool isTile = true);
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;
  bool isATile() { return isTile; }

private:
  bool isTile;
  Reactive* pReactive = 0;
  Sprite* pSprite = 0;
  Transform* pTransform = 0;
  GameObjectComposition* parent = 0;
};

#endif