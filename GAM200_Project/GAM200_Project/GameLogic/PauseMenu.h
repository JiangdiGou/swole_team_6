#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../Engine.h"
#include "PauseMenuButton.h"

enum menuSate {MAINMENU = 0, AREYOUSURE, INSTRUCTIONS};

class PauseMenu : public ISystem
{
  friend class MenuButton;

public:

  PauseMenu();
  void Initialize();
  void Update(float dt);
  void SendMessages(Message* message);

private:
  void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset);
  std::vector<GOC*> pauseMenuObjects;
  menuSate state = MAINMENU;
};

extern PauseMenu* PAUSEMENU;

#endif