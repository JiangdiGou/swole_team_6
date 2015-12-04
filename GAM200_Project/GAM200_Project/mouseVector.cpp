/*****************************************************************************/
/*!
\file    mouseVector.cpp
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Implementation of Mousevector, which stores mouse up and mouse down events
  in order to store a vector of a mouse drag. It also debug draws the
  vector on the screen
\remarks 
  There's a good chance this won't be in the final build of the game. This
  was really just to prove that this was possible since it was our main
  mechanic and this technology needed to exist

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#include "mouseVector.h"
#include "physicsLib/RayLineBoxCollision.h"
#include "engineAudio/SoundEmitter.h"

void MouseVector::SendMessages(Message * message)
{
	parent = GetOwner();
	//mouseSound = reinterpret_cast<SoundEmitter *>(parent->GetComponent(CT_SoundEmitter));
  switch (message->MessageId)
  {
  case Mid::MouseButton:
  {
    MouseButton* mouseEvent = (MouseButton*)message;

    if (mouseEvent->MouseButtonIndex == 0)
    {
      if (mouseEvent->ButtonIsPressed)
      {
		  //mouseSound.Initialize();
		  //mouseSound.PlayEvent("SwordSwing");
        mouseDown = true;
        mouseDownPos = mouseEvent->MousePosition;
		//LoopAll(Vector2(mouseDownPos), Vector2(mouseUpPos));
      }
      else if (mouseDown && !(mouseEvent->ButtonIsPressed))
      {
		  //mouseSound.Initialize();
		  //mouseSound.PlayEvent("SwordHitOrganic");
        mouseDown = false;
        mouseUpPos = mouseEvent->MousePosition;
		
		    objsInRay = LoopAll(Vec2D(mouseDownPos), Vec2D(mouseUpPos));
		
      }
    }
  }
  }
}

GameObjectComposition* MouseVector::GetRayResult(int index)
{
  return objsInRay.at(index);
}

void MouseVector::Update(float dt)
{
  if (!mouseDown)
  {
	GetOwner()->has(PlayerAttack);
    debugDrawLine(Vector3(mouseDownPos, 0), Vector3(mouseUpPos, 0), Vector3());
  }
}

void MouseVector::SerializeRead(Serializer& str)
{


}
void MouseVector::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);

}

ZilchDefineType(MouseVector, "MouseVector", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindField(builder, type, &MouseVector::mouseDownPos, "mouseDownPos", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &MouseVector::mouseUpPos, "mouseUpPos", PropertyBinding::GetSet);
  ZilchBindMethod(builder, type, &MouseVector::GetRayResult, ZilchNoOverload, "GetRayResult", ZilchNoNames);
}