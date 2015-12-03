#pragma once

#include "../Component.h"
#include "../reactive.h"

class HealthManager : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void UpdateHealth(int val);

  HealthManager();

private:
	//enum  EnemyState { CHASING, PACING, ATTACKING };

  Transform* pTransform;
  Sprite *pSprite;
  GOC* player;
  
  int TotalHealth;
  int CurrentHealth;

  bool CanMove = true;
  bool MovingRight;
  bool Alive = true;
};