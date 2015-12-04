#pragma once

#include "../Component.h"
#include "../reactive.h"
#include "PlayerHealthBar.h"

class HealthManager : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void UpdateHealth(int val);
  void UpdateScale(float scale);

  HealthManager();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  

  int TotalHealth;
  int CurrentHealth;

  bool CanMove = true;
  bool MovingRight;
  bool Alive = true;
};