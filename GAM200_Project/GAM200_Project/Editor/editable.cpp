#include "editable.h"

void Editable::Initialize()
{
  parent = GetOwner();
  pReactive = reinterpret_cast<Reactive *>(parent->GetComponent(CT_Reactive));
}

void Editable::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    //If no focus, and left click, and moused over this tile, this is focus
    if (GUIMGR->getFocus() == NULL
      && mouseEvent->MouseButtonIndex == 0
      && mouseEvent->ButtonIsPressed
      && pReactive->mouseOver())
    {
      GUIMGR->setFocus(parent);
    }
  }
  }
}

void Editable::Update(float dt)
{
  Sprite* ownerSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));
  if (ownerSprite)
  {
    //Highlighting for tile selection
    if (pReactive->mouseOver() && GUIMGR->getFocus() == NULL)
      ownerSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0f);
    else if (GUIMGR->getFocus() == parent)
      ownerSprite->color = glm::vec4(0.0, 1.0, 0.0, 1.0f);
    else
      ownerSprite->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
  }
}