#pragma once

#include "../Component.h"
#include "../reactive.h"

class PlayerHealthBar : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void UpdateScale(float scale);

  PlayerHealthBar();

private:

  Transform* pTransform;
  Sprite *pSprite;
  GOC* player;
  Vector3 originScale;
  int TotalHealth;
  int CurrentHealth;
};