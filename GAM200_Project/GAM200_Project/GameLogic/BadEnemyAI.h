#pragma once

#include "../Component.h"
#include "../reactive.h"

class BadEnemyAI : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void UpdateHealth(int val);

  BadEnemyAI();

private:
  Transform* pTransform;
  Vector3D paceDistance;
  float waitTime;
  
  int TotalHealth;
  int CurrentHealth;


  bool MovingRight;
};