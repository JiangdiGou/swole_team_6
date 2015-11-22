#include "editable.h"

Editable::Editable(bool isTile)
{
  this->isTile = isTile;
}

void Editable::Initialize()
{
  parent = GetOwner();
  pReactive = reinterpret_cast<Reactive *>(parent->GetComponent(CT_Reactive));
  pSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));
  pTransform = reinterpret_cast<Transform *>(parent->GetComponent(CT_Transform));
}

void Editable::SendMessages(Message* message)
{
  
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    //All left click stuff is figured out by reactive. 
    //If Right click
    if (mouseEvent->MouseButtonIndex == 1 && pReactive->mouseOver())
    {
      if (isTile)
        GUIMGR->tilemapTools->changeTile(parent, true);
    }
  }
  }
}


void Editable::Update(float dt)
{
  //Tile chaging / entity selection
  if (pReactive->mouseDownAndOver())
  {
    if (isTile && GUIMGR->tilemapTools->isActive())
      GUIMGR->tilemapTools->changeTile(parent);
    else if (!isTile)
      GUIMGR->entityTools->setFocus(parent);
  }

  //Transform Stuff
  //Rotation
  if (pReactive->mouseDownHeldAndOver() && !isTile && pReactive->ctrlPressed())
  {
    debugDrawCircle(pTransform->GetPosition(), 2, Vector3(), 100);
    Vector2 mousePos = pReactive->getMousePos();
    Vector2 mouseRadius = mousePos - pTransform->GetPositionXY();
    mouseRadius = mouseRadius.Normalize();

    //Gets angle of rotation
    float angle;
    if (mouseRadius.x > 0)
      angle = asin(mouseRadius.y);
    else if (mouseRadius.x < 0 && mouseRadius.y < 0)
      angle = -acos(mouseRadius.x);
    else
      angle = acos(mouseRadius.x);

    pTransform->SetRotation(Vector3(0, 0, angle));
  }
  //Scale
  else if (pReactive->mouseDownHeldAndOver() && !isTile && pReactive->shiftPresed())
  {
    debugDrawSquare(pTransform->GetPosition(), 2 * pTransform->GetScale().x, 
      2 * pTransform->GetScale().y, Vector3());

    Vector2 mousePos = pReactive->getMousePos();
    Vector2 mouseRadius = mousePos - pTransform->GetPositionXY();

    float scalX = mouseRadius.x;
    float scalY = mouseRadius.y;

    pTransform->SetScale(Vector2(scalX, scalY));
  }
  //Translate
  else if (pReactive->mouseDownHeldAndOver() && !isTile)
    pTransform->SetPosition(pReactive->getMousePos());

  //Selection highlighting
  if (pSprite)
  {
    //Highlighting for tile selection
    if (pReactive->mouseOver())
    {
      if (!isTile)
        pSprite->color = glm::vec4(0.5, 0.5, 0.0, 1.0f);
      else if (GUIMGR->tilemapTools->isActive())
        pSprite->color = glm::vec4(1.0, 1.0, 0.0, 1.0f);
    }
    else if (!isTile && GUIMGR->entityTools->getFocus() == parent)
      pSprite->color = glm::vec4(0.0, 1.0, 0.0, 1.0f);
    else
      pSprite->color = glm::vec4(1.0, 1.0, 1.0, 1.0);
  }
}