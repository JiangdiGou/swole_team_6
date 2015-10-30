#include "mouseVector.h"

void mouseVector::SendMessages(Message * message)
{
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;
    Transform* playerTransform = LOGIC->player->has(Transform);

    if (mouseEvent->MouseButtonIndex == 0)
    {
      if (mouseEvent->ButtonIsPressed)
      {
        //std::cout << "Pressed " << std::endl;
        mouseDown = true;

        Vector2 mousePos = mouseEvent->MousePosition;
        //Magic af
        mousePos.x = mousePos.x / 200.0f;
        mousePos.y = mousePos.y / 200.0f;

        mouseDownPos = mousePos + playerTransform->GetPositionXY();
      }
      else if (mouseDown && !(mouseEvent->ButtonIsPressed))
      {
        mouseDown = false;
        //std::cout << "unpressed " << std::endl;
        Vector2 mousePos = mouseEvent->MousePosition;
        //Magic af
        mousePos.x = mousePos.x / 200.0f;
        mousePos.y = mousePos.y / 200.0f;

        mouseUpPos = mousePos + playerTransform->GetPositionXY();

      }
    }
  }
  }
}

void mouseVector::Update(float dt)
{
  if (!mouseDown)
  {
    //std::cout << mouseDownPos.x << " " << mouseDownPos.y << " " << std::endl;
    //std::cout << mouseUpPos.x << " " << mouseUpPos.y << " " << std::endl;

    //debugDrawLine(Vector3(mouseDownPos), Vector3(mouseUpPos), Vector3());
  }
}

 