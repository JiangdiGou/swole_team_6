#pragma once

#include "../Component.h"
#include "../reactive.h"

class HUDcomponent : public GameComponent
{
public:
	void Initialize()override;
	void Update(float dt)override;
	void SendMessages(Message* msg)override;
	void SerializeWrite(Serializer& str) override;

	HUDcomponent();

private:
	Reactive* pReactive;
	Transform* pTransform;
	Transform* camPos;
	bool CurrMouseState;
	bool MouseDown;
};