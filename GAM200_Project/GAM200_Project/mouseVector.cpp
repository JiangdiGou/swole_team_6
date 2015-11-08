/*****************************************************************************/
/*!
\file    mouseVector.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of Mousevector, which stores mouse up and mouse down events
  in order to store a vector of a mouse drag. It also debug draws the
  vector on the screen
\remarks 
  There's a good chance this won't be in the final build of the game. This
  was really just to prove that this was possible since it was our main
  mechanic and this technology needed to exist

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "mouseVector.h"

void mouseVector::SendMessages(Message * message)
{
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    if (mouseEvent->MouseButtonIndex == 0)
    {
      if (mouseEvent->ButtonIsPressed)
      {
        mouseDown = true;
        mouseDownPos = mouseEvent->MousePosition;
      }
      else if (mouseDown && !(mouseEvent->ButtonIsPressed))
      {
        mouseDown = false;
        mouseUpPos = mouseEvent->MousePosition;
      }
    }
  }
  }
}

void mouseVector::Update(float dt)
{
  if (!mouseDown)
  {
    debugDrawLine(Vector3(mouseDownPos), Vector3(mouseUpPos), Vector3());
  }
}

 
