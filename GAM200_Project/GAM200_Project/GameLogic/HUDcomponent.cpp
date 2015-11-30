#include "HUDcomponent.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void HUDcomponent::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);
	pCam = GRAPHICS->getCamera();
}

void HUDcomponent::Update(float dt)
{
	GOC* owner = GetOwner();

	pTransform->SetPosition(pCam->getPosition() + offset);
}

void HUDcomponent::SendMessages(Message* message)
{
}

void HUDcomponent::SerializeRead(Serializer& str)
{
	StreamRead(str, offset.x);
	StreamRead(str, offset.y);
	StreamRead(str, offset.z);
}

void HUDcomponent::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
	  StreamWrite(str, offset.x);
	  StreamWrite(str, offset.y);
	  StreamWrite(str, offset.z);
	  StreamWrite(str);
}

HUDcomponent::HUDcomponent()
{

}