#pragma once

#include "../Component.h"
#include "../reactive.h"
#include "LoadLevel.h"
#include "GameReactive.h"
#include "PauseMenu.h"

class QuitGame : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;

  QuitGame();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  GameReactive* pReactive;
  

 
};