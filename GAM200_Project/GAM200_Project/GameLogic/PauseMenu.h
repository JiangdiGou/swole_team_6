#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../Engine.h"
#include "PauseMenuButton.h"

class PauseMenu : public ISystem
{
public:

  PauseMenu();
  void Initialize();
  void Update(float dt);
  void SendMessages(Message* message);


private:
  void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset);
  std::vector<GOC*> pauseMenuObjects;
};

extern PauseMenu* PAUSEMENU;

#endif