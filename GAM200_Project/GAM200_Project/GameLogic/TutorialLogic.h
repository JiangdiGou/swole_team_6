#pragma once

#include "../Component.h"
#include "../reactive.h"
#include <string>

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
  int dist;
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;

  std::string levelName;

  float delayTimer;
  bool loadLevel = false;
};