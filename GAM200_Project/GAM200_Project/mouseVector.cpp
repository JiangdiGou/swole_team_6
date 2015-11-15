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
#include "physicsLib/RayLineBoxCollision.h"

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
		//LoopAll(Vector2(mouseDownPos), Vector2(mouseUpPos));
      }
      else if (mouseDown && !(mouseEvent->ButtonIsPressed))
      {
        mouseDown = false;
        mouseUpPos = mouseEvent->MousePosition;
		LoopAll(Vec2D(mouseDownPos), Vec2D(mouseUpPos));
      }
    }
  }
  }
}

void mouseVector::Update(float dt)
{
  if (!mouseDown)
  {
    debugDrawLine(Vector3(mouseDownPos, 0), Vector3(mouseUpPos, 0), Vector3());
  }
}

void mouseVector::SerializeRead(Serializer& str)
{


}
void mouseVector::SerializeWrite(Serializer& str)
{


}
