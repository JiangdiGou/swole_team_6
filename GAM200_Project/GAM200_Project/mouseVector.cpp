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
      std::cout << "HAPPENED" << std::endl;
      mouseUpPos = glm::vec2(
        mouseEvent->MousePosition.x, mouseEvent->MousePosition.y);

      glm::mat4 cameraMat = glm::ortho(
        (float)((float)-INITINFO->clientWidth / (1000.0f*0.25)),
        (float)((float)INITINFO->clientWidth / (1000.0f*0.25)),
        (float)((float)-INITINFO->clientHeight / (1000.0f*0.25)),
        (float)((float)INITINFO->clientHeight / (1000.0f*0.25)),
        0.1f, 5.0f);

      glm::vec4 transformedPos = cameraMat * glm::vec4(mouseUpPos, 0, 0);

      mouseUpPos = glm::vec2(transformedPos.x, transformedPos.y);
      std::cout << mouseUpPos.x << ", " << mouseUpPos.y << std::endl;
    }
  }
  }
}

 