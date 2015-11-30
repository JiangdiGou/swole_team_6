#include "PauseMenuButton.h"

MenuButton::MenuButton(buttonType newButtonType) : type(newButtonType)
{
}

void MenuButton::Initialize()
{
  pReactive = (GameReactive*)GetOwner()->has(GameReactive);
}

void MenuButton::Update(float dt)
{
  if (pReactive->mouseDownAndOver())
  {
    switch (type)
    {
    case RESUME:
    {
      pReactive->setDefaultOverride();
      CORE->Pause = false;
      break;
    }
    default:
    {
      return;
    }
    }
  }
}
