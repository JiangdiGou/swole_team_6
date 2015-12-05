#pragma once

#include "../Component.h"
#include "../reactive.h"

class TutorialLogic : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void LoadNextLevel();

  TutorialLogic();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;

  float delayTimer;
  boolean loadLevel = false;
};