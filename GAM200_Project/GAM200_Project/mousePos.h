#include "WindowsSystem.h"
#include <iostream>

extern POINT mousePos;
POINT mousePos;
void updateMousePos()
{
  if (GetCursorPos(&mousePos))
  {
    if (ScreenToClient(WINDOWSSYSTEM->hWnd, &mousePos))
    {
      mousePos.y = WINDOWSSYSTEM-> - mousePos.y;
      std::cout << mousePos.x << ", " << mousePos.y << std::endl;
    }
  }

}