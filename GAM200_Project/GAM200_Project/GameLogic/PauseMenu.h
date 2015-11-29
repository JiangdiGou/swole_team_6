#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "../Engine.h"

class PauseMenu : public ISystem
{
public:

  void Initialize();
  void Update(float dt);
  void SendMessages(Message* message);


private:
  void PauseMenu::followCameraWithOffset(GOC* follower, Vector2 offset);
  std::vector<GOC*> pauseMenuObjects;
};

#endif