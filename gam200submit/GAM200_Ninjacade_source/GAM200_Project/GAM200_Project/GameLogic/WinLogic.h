/******************************************************************************/
/*!
\author Josh Painter

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include "../Component.h"
#include "../reactive.h"

class WinLogic : public GameComponent
{
public:
  void Initialize()override;
  void Update(float dt)override;
  void SendMessages(Message* msg)override;
  void SerializeWrite(Serializer& str) override;
  void KillCounterPlus();

  WinLogic();

private:
  Transform* pTransform;
  Sprite *pSprite;
  GOC* parent;
  int numEnemies;
  int totalEnemies;
 
};