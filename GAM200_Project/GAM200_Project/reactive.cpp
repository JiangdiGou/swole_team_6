#include "reactive.h"

Reactive::Reactive(bool actuallyReactive)
{
  trueReactive = actuallyReactive;
}

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
    control = false;
    alt = false;
    shift = false;

    //std::cout << "ID: " << message->MessageId << std::endl;
  case Mid::MouseMove:
  {

    MouseMove* moveEvent = (MouseMove*)message;
    mousePos = moveEvent->MousePosition;

    float leftEdge, rightEdge, topEdge, bottomEdge;

    //Checks if it needs to flip right and left edges
    if (ownerTransform->GetScale().x > 0)
    {
      leftEdge = ownerTransform->GetPositionX() - 0.5 * ownerTransform->GetScale().x;
      rightEdge = ownerTransform->GetPositionX() + 0.5 * ownerTransform->GetScale().x;
    }
    else
    {
      leftEdge = ownerTransform->GetPositionX() + 0.5 * ownerTransform->GetScale().x;
      rightEdge = ownerTransform->GetPositionX() - 0.5 * ownerTransform->GetScale().x;
    }

    //Checks if it needs to flip top and bot edges
    if (ownerTransform->GetScale().y > 0)
    {
      topEdge = ownerTransform->GetPositionY() + 0.5 * ownerTransform->GetScale().y;
      bottomEdge = ownerTransform->GetPositionY() - 0.5 * ownerTransform->GetScale().y;
    }
    else
    {
      topEdge = ownerTransform->GetPositionY() - 0.5 * ownerTransform->GetScale().y;
      bottomEdge = ownerTransform->GetPositionY() + 0.5 * ownerTransform->GetScale().y;
    }

    if (moveEvent->MousePosition.x < rightEdge && moveEvent->MousePosition.x > leftEdge
      && moveEvent->MousePosition.y > bottomEdge && moveEvent->MousePosition.y < topEdge)
      mouseIsOverThis = true;
    else
      mouseIsOverThis = false;

    break;
  }
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    control = mouseEvent->mods & GLFW_MOD_CONTROL;
    alt = mouseEvent->mods & GLFW_MOD_ALT;
    shift = mouseEvent->mods & GLFW_MOD_SHIFT;

    //For Left click
    if (mouseEvent->MouseButtonIndex == 0)
    {
      //if its pressed 
      if (mouseEvent->ButtonIsPressed && mouseIsOverThis)
      {
        mouseDownOnThis = true;
        break;
      }
      //If its not pressed 
      else if (mouseDownOnThis)
      {
        mouseDownOnThis = false;
        break;
      }
    }
  }
  }
}

void Reactive::Update(float dt)
{
  if (mouseDownOnThis)
  {
    if (mouseHoldCounter > 5)
      mouseHeldOnThis = true;
    else
    {
      mouseHoldCounter++;
      mouseHeldOnThis = false;
    }
  }
  else
  {
    mouseHoldCounter = 0;
    mouseHeldOnThis = false;
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