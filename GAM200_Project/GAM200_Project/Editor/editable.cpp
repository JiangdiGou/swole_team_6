#include "editable.h"

Editable::Editable(bool isTile)
{
  this->isTile = isTile;
}

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

    //If you left clicked this object
    if (mouseEvent->MouseButtonIndex == 0
      && mouseEvent->ButtonIsPressed
      && pReactive->mouseOver())
    {
      if (isTile && GUIMGR->tilemapTools->isActive())
        GUIMGR->tilemapTools->changeTile(parent);
      else if (!isTile)
        GUIMGR->entityTools->setFocus(parent);
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
    if (pReactive->mouseOver())
    {
      if (!isTile)
       ownerSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0f);
      else if (GUIMGR->tilemapTools->isActive())
        ownerSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0f);
    }
    else if (!isTile && GUIMGR->entityTools->getFocus() == parent)
      ownerSprite->color = glm::vec4(0.0, 1.0, 0.0, 1.0f);
    else
      ownerSprite->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
  }
}