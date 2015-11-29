#include "editable.h"

Editable::Editable(bool isTile)
{
  this->isTile = isTile;
}

void Editable::Initialize()
{
  parent = GetOwner();
  pSprite = reinterpret_cast<Sprite *>(parent->GetComponent(CT_Sprite));
  pTransform = reinterpret_cast<Transform *>(parent->GetComponent(CT_Transform));
  
  assert(fetchTransform());
}

void Editable::SendMessages(Message* message)
{
  updateMouseFlags(message);

  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    //All left click stuff is figured out by reactive. 
    //If Right click
    if (mouseEvent->MouseButtonIndex == 1 && mouseOver())
    {
      if (isTile)
        GUIMGR->tilemapTools->changeTile(parent, true);
    }
  }
  }
}


void Editable::Update(float dt)
{
  checkMouseHeld();

  if (ImGui::GetIO().WantCaptureMouse)
    return;

  //Tile chaging / entity selection
  if (mouseDownAndOver())
  {
    if (isTile && GUIMGR->tilemapTools->isActive())
      GUIMGR->tilemapTools->changeTile(parent);
    else if (!isTile)
      GUIMGR->entityTools->setFocus(parent);
  }

  //Transform Stuff
  //Rotation
  if (mouseDownHeldAndOver() && !isTile && ctrlPressed())
  {
    debugDrawCircle(pTransform->GetPosition(), 2, Vector3(), 100);
    Vector2 mousePos = getMousePos();
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
  else if (mouseDownHeldAndOver() && !isTile && shiftPresed())
  {
    debugDrawSquare(pTransform->GetPosition(), 2 * pTransform->GetScale().x, 
      2 * pTransform->GetScale().y, Vector3());

    Vector2 mousePos = getMousePos();
    Vector2 mouseRadius = mousePos - pTransform->GetPositionXY();

    float scalX = mouseRadius.x;
    float scalY = mouseRadius.y;

    pTransform->SetScale(Vector2(scalX, scalY));
  }
  //Translate
  else if (mouseDownHeldAndOver() && !isTile)
    pTransform->SetPosition(getMousePos());

  //Selection highlighting
  if (pSprite)
  {
    //Highlighting for tile selection
    if (mouseOver())
    {
      if (isTile && GUIMGR->tilemapTools->isActive())
        pSprite->color = glm::vec4(highlightColor.x, highlightColor.y, highlightColor.z, 1);
      else if (!isTile && GUIMGR->entityTools->getFocus() != parent)
        pSprite->color = glm::vec4(highlightColor.x, highlightColor.y, highlightColor.z, 1);
      else if (!isTile && GUIMGR->entityTools->getFocus() == parent)
        pSprite->color = glm::vec4(selectionColor.x, selectionColor.y, selectionColor.z, 1);
    }
    else
      pSprite->color = glm::vec4(1, 1, 1, 1);


  }
}