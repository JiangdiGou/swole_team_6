#pragma once

#include "../Component.h"
#include "../reactive.h"
#include "LoadLevel.h"
#include "GameReactive.h"

class LoadLevel : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;

  LoadLevel();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  GameReactive* pReactive;
  

 
};