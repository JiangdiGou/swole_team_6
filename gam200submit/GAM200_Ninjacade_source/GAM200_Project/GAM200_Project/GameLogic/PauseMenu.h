/******************************************************************************/
/*!
\author Mitch Regan

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../Engine.h"
#include "PauseMenuButton.h"
#include "../engineAudio/SoundEmitter.h"

enum menuSate {MAINMENU = 0, AREYOUSURE, INSTRUCTIONS};

class PauseMenu : public ISystem
{
  friend class MenuButton;

public:

  PauseMenu();
  void Initialize();
  void Update(float dt);
  void SendMessages(Message* message);

  menuSate state = MAINMENU;

  

private:
	SoundEmitter * emitter;
  void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset);
  std::vector<GOC*> pauseMenuObjects;
};

extern PauseMenu* PAUSEMENU;

#endif