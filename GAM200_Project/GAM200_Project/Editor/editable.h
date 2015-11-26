#ifndef EDITABLE_H
#define EDITABLE_H

//This is the interface  for the editor into components.

#include "../Component.h"
#include "../reactive.h"
#include "imGuiManager.h"

class Editable : public Reactive
{
public:
  Editable(bool isTile = true);
  void Initialize() override;
  void Update(float dt);
  bool isATile() { return isTile; }
  void SendMessages(Message* message) override;

  Vector3 getActualColor() { return actualColor; }

private:
  Vector3 actualColor;
  Vector3 highlightColor = Vector3(0.5241, 0.5241, 0);
  Vector3 selectionColor = Vector3(0, .9562, 0);

  bool isTile;
  Sprite* pSprite = 0;
  Transform* pTransform = 0;
  GameObjectComposition* parent = 0;
};

#endif