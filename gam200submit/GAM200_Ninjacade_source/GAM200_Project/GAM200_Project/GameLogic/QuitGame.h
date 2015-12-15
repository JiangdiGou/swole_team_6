/******************************************************************************/
/*!
\author Mitch Regan

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include "../Component.h"
#include "../reactive.h"
#include "LoadLevel.h"
#include "GameReactive.h"
#include "PauseMenu.h"

enum QuitButtonTypes {QB_Quit, QB_Yes, QB_No};

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
  void SwitchQuitState();
  QuitButtonTypes Type;
  

 
};