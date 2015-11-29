#include "HUDcomponent.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void HUDcomponent::Initialize()
{
	GOC* parent = GetOwner();
	pTransform = parent->has(Transform);
	Camera* cPtr = GRAPHICS->getCamera();
	GOC* camera = cPtr->GetOwner();
	camPos = camera->has(Transform);
}

void HUDcomponent::Update(float dt)
{
	GOC* owner = GetOwner();

	pTransform->SetPosition(camPos->GetPosition() + offset);
}

void HUDcomponent::SendMessages(Message* message)
{
}

void HUDcomponent::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  StreamWrite(str);
}

HUDcomponent::HUDcomponent()
{

}