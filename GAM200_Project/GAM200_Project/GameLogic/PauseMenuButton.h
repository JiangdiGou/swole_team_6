#ifndef PAUSEMENUBUTTON_H
#define PAUSEMENUBUTTON_H

#include "../Composition.h"
#include "GameReactive.h"
#include "../Core.h"

enum buttonType { HOWTOPLAY = 0, RESUME, QUIT};

class MenuButton : public GameComponent
{
public:
  MenuButton(buttonType newButtonType);

  void Initialize();
  void Update(float dt);

private:
  GameReactive* pReactive;
  buttonType type;
};

#endif
