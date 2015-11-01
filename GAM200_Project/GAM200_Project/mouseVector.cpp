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

 