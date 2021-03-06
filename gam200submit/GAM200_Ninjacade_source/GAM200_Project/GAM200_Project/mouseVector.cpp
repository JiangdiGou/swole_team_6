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
#include "GameLogic\PlayerAttack.h"

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
		  //I don't know if gameplay programmer is going to add attack sound or not, but before
		  //submission, if the gameplay programmer find sth breaks becuz of the sound code below,
		  //comment it out and make your own attack sound code sheet. I'm not responsible for when
		  // someone who said"I can work on that too.""I need you to tell me how to access it".. but
		  // never do anythings, if you cant do it, say you cant, if you can, do it asap. jg
		  SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		  emitter->SetVolume(1.0f,"SwordSwing");
		  emitter->StopEvent("SwordSwing");
		  emitter->PlayEvent("SwordSwing");
		  //mouseSound.Initialize();
		  //mouseSound.PlayEvent("SwordSwing");
        mouseDown = true;
        mouseDownPos = mouseEvent->MousePosition;
		//LoopAll(Vector2(mouseDownPos), Vector2(mouseUpPos));
      }
      else if (mouseDown && !(mouseEvent->ButtonIsPressed))
      {
		  //SoundEmitter* emitter = reinterpret_cast<SoundEmitter*>(LOGIC->player->GetComponent(CT_SoundEmitter));
		  //emitter->SetVolume(1.0f, "SwordHitOrganic");
		  //emitter->StopEvent("SwordHitOrganic");
		  //emitter->PlayEvent("SwordHitOrganic");
		  //mouseSound.Initialize();
		  //mouseSound.PlayEvent("SwordHitOrganic");
        mouseDown = false;
        mouseUpPos = mouseEvent->MousePosition;
		    
        //call the player attack
        PlayerAttack* playerAttack = parent->has(PlayerAttack);

		    objsInRay = LoopAll(Vec2D(mouseDownPos), Vec2D(mouseUpPos));

        if (playerAttack != nullptr)
         playerAttack->Attack(objsInRay, mouseDownPos, mouseUpPos);
		
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