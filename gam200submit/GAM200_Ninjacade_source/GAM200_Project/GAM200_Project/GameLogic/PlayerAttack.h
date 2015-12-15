/******************************************************************************/
/*!
\author Mitch Regan

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
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
  void Attack(std::vector <GameObjectComposition*> objectsHit, Vec2D start, Vec2D end);

  PlayerAttack();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  Body* playerBody;
  //pMouse;
  

  float startPos;
  float endPos;

  float slashTimer;

  bool CanSlash = true;
  bool CanMove = true;
  bool MovingRight;
  bool Alive = true;
};