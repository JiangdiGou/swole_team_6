#include "TestComponent.h"
#include "../physicsLib/math_utility.h"

//playerstate component for reference
void TestComponent::Initialize()
{
	GOC* parent = GetOwner();
	pReactive = parent->has(Reactive);
	pTransform = parent->has(Transform);
}
void TestComponent::Update(float dt)
{
	GOC* owner = GetOwner();

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
void TestComponent::SendMessages(Message* message)
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

TestComponent::TestComponent()
{

}