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

    if (moveEvent->MousePosition.x <
      ownerTransform->GetPositionX() + 0.5 * ownerTransform->GetScale().x
      && moveEvent->MousePosition.x >
      ownerTransform->GetPositionX() - 0.5 * ownerTransform->GetScale().x
      && moveEvent->MousePosition.y <
      ownerTransform->GetPositionY() + 0.5 * ownerTransform->GetScale().y
      && moveEvent->MousePosition.y >
      ownerTransform->GetPositionY() - 0.5 * ownerTransform->GetScale().y)
    {
      mouseIsOver = true;
      std::cout << moveEvent->MousePosition << " is within box." << std::endl;
      std::cout << "box has pos " << ownerTransform->GetPosition() << " and scale " << ownerTransform->GetScale() << std::endl;
    }
    else
    {
      std::cout << moveEvent->MousePosition << " is not within box." << std::endl;
      std::cout << "box has pos " << ownerTransform->GetPosition() << " and scale " << ownerTransform->GetScale() << std::endl;
      mouseIsOver = false;
    }
  }
  }
}

bool Reactive::mouseOver()
{
  return mouseIsOver;
}

void Reactive::Update(float dt)
{
  GameObjectComposition* parent = GetOwner();
  Sprite* ownerSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));

  if (ownerSprite)
  {
    if (mouseIsOver)
      ownerSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0);
    else
      ownerSprite->color = glm::vec4(1.0, 0.0, 1.0, 1.0);
  }
}