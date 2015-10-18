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
      //Get Window height from gabe, windowheight - mousepos.y will flip it so 0,0 is the bottom left corner 
      //mousePos.y = WINDOWSSYSTEM-> - mousePos.y;
      //std::cout << mousePos.x << ", " << mousePos.y << std::endl;
    }
  }

}