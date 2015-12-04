#include "PauseMenuButton.h"
#include "PauseMenu.h"

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
      GRAPHICS->toggleBackground(true);
      break;
    }
    case QUIT:
    {

		
      PAUSEMENU->state = AREYOUSURE;
      break;
    }
    case IAMSURE:
    {

      CORE->GameActive = false;
      break;
    }
    case IAMNOTSURE:
    {

      PAUSEMENU->state = MAINMENU;
      break;
    }
    case HOWTOPLAY:
    {

      PAUSEMENU->state = INSTRUCTIONS;
      break;
    }
    case GOBACK:
    {

      PAUSEMENU->state = MAINMENU;
      break;
    }
    default:
    {
      return;
    }
    }
  }
}
