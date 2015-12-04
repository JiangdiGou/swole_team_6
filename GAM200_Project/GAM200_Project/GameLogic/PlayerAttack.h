#pragma once

#include "../Component.h"
#include "../reactive.h"

class PlayerAttack : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void Attack();

  PlayerAttack();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  //pMouse;
  

  float startPos;
  float endPos;

  bool CanMove = true;
  bool MovingRight;
  bool Alive = true;
};