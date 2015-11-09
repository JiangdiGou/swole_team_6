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

 