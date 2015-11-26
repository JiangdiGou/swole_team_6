#include "reactive.h"


bool Reactive::fetchTransform()
{
  GameObjectComposition* parent = GetOwner();
  ownerTransform = reinterpret_cast<Transform *>(parent->GetComponent(CT_Transform));

  if (ownerTransform == NULL)
    return false;
  else
    return true;
}

bool Reactive::checkMouseHeld()
{
  if (mouseDownOnThis)
  {
    if (mouseHoldCounter > 5)
    {
      mouseHeldOnThis = true;
      return true;
    }
    else
    {
      mouseHoldCounter++;
      mouseHeldOnThis = false;
      return false;
    }
  }
  else
  {
    mouseHoldCounter = 0;
    mouseHeldOnThis = false;
    return false;
  }
}

void Reactive::updateMouseFlags(Message* message)
{
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

ZilchDefineType(Reactive, "Reactive", ZLib_Internal, builder, type)
{

  ZilchBindMethod(builder, type, &Reactive::mouseOver, ZilchNoOverload, "mouseOver", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::mouseDownAndOver, ZilchNoOverload, "mouseDownAndOver", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::mouseDownHeldAndOver, ZilchNoOverload, "mouseDownHeldAndOver", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::ctrlPressed, ZilchNoOverload, "ctrlPressed", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::altPressed, ZilchNoOverload, "altPressed", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::shiftPresed, ZilchNoOverload, "shiftPresed", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::isActuallyReactive, ZilchNoOverload, "isActuallyReactive", ZilchNoNames);
  ZilchBindMethod(builder, type, &Reactive::getMousePos, ZilchNoOverload, "getMousePos", ZilchNoNames);
}