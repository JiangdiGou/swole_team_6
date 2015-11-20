#pragma once

#include "../Component.h"
#include "../reactive.h"

class TestComponent : public GameComponent
{
public:
	void Initialize()override;
	void Update(float dt)override;
	void SendMessages(Message* msg)override;

	TestComponent();

private:
	Reactive* pReactive;
	Transform* pTransform;
	bool CurrMouseState;
	bool MouseDown;
};