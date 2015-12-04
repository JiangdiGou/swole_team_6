#pragma once

#include "../Component.h"
#include "../reactive.h"
#include "HealthManager.h"

class BadEnemyAI : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;

  BadEnemyAI();

private:
	enum  EnemyState { CHASING, PACING, ATTACKING };

  Transform* pTransform;
  Sprite *pSprite;
  Vector3D paceDistance;
  float waitTime;
  float attackCooldown;
  EnemyState CurrentState;
  GOC* player;
  HealthManager* playerHM;

  bool CanMove = true;
  bool MovingRight;
};