#include "reactive.h"

void Reactive::Initialize()
{
  GameObjectComposition* parent = GetOwner();
  ownerTransform = reinterpret_cast<Transform *>(parent->GetComponent(CT_Transform));
}

void Reactive::SendMessages(Message * message)
{
  //std::cout << "mouse moved!" << std::endl;
  switch (message->MessageId)
  {
    //std::cout << "ID: " << message->MessageId << std::endl;
  case Mid::MouseMove:
  {

    MouseMove* moveEvent = (MouseMove*)message;

    float leftEdge = ownerTransform->GetPositionX() - 0.5 * ownerTransform->GetScale().x;
    float rightEdge = ownerTransform->GetPositionX() + 0.5 * ownerTransform->GetScale().x;
    float topEdge = ownerTransform->GetPositionY() + 0.5 * ownerTransform->GetScale().y;
    float bottomEdge = ownerTransform->GetPositionY() - 0.5 * ownerTransform->GetScale().y;

    if (moveEvent->MousePosition.x < rightEdge && moveEvent->MousePosition.x > leftEdge
      && moveEvent->MousePosition.y > bottomEdge && moveEvent->MousePosition.y < topEdge)
      mouseIsOver = true;
    else
      mouseIsOver = false;
  }
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    if (mouseEvent->MouseButtonIndex == 0)
    {
      if (mouseEvent->ButtonIsPressed)
        mouseDown = true;
      else
        mouseDown = false;
    }
  }
  }
}
void Reactive::SerializeRead(Serializer& str)
{

}
void Reactive::SerializeWrite(Serializer& str) 
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
}

bool Reactive::mouseOver()
{
  return mouseIsOver;
}

void Reactive::Update(float dt)
{
  GameObjectComposition* parent = GetOwner();
  Sprite* ownerSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));

  /*
  if (ownerSprite)
  {
    if (mouseIsOver && mouseDown)
      ownerSprite->color = glm::vec4(0.0, 1.0, 0.0, 1.0);
    else if (mouseIsOver)
      ownerSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    else
      ownerSprite->color = glm::vec4(1.0, 0.0, 0.0, 1.0);
  }*/
}