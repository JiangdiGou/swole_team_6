#include "HUDcomponent.h"
#include "../physicsLib/math_utility.h"
#include "../engineGraphics/graphicsManager.h"

//playerstate component for reference
void HUDcomponent::Initialize()
{
	GOC* parent = GetOwner();
	pReactive = parent->has(GameReactive);
	pTransform = parent->has(Transform);
	Camera* cPtr = GRAPHICS->getCamera();
	GOC* camera = cPtr->GetOwner();
	camPos = camera->has(Transform);
}

void HUDcomponent::Update(float dt)
{
	GOC* owner = GetOwner();

	pTransform->SetPosition(camPos->GetPosition() + Vector3(-1,2,0));

	if (pReactive->mouseOver() && !CurrMouseState)
	{
		CurrMouseState = true;
		Vector3D sizeChange = Vector3(2,1,0);
		pTransform->SetScale((pTransform->GetScale()) + sizeChange);
	}

	if (!pReactive->mouseOver() && (CurrMouseState == true))
	{
		CurrMouseState = false;

		Vector3D sizeChange = Vector3(2, 1, 0);
		pTransform->SetScale((pTransform->GetScale()) - sizeChange);
	}
	


}
void HUDcomponent::SendMessages(Message* message)
{
	switch (message->MessageId)
	{
	case Mid::MouseButton:
	{
		MouseButton* mouseEvent = (MouseButton*)message;

		if (mouseEvent->MouseButtonIndex == 0)
		{
			if (mouseEvent->ButtonIsPressed)
			{
				MouseDown = true;
			}
			else if (MouseDown && !(mouseEvent->ButtonIsPressed) && pReactive->mouseOver())
			{
				MouseDown = false;

				//Load the next level here
			}
		}
	}
	}
}

void HUDcomponent::SerializeWrite(Serializer& str)
{
	  StreamWrite(str, (int&)TypeId);
	  //StreamWrite(str, Vector3D(1, 1, 1));
	  StreamWrite(str);
}

HUDcomponent::HUDcomponent()
{

}