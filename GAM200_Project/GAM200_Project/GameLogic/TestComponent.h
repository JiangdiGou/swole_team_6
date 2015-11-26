#pragma once

#include "../Component.h"
#include "GameReactive.h"

class TestComponent : public GameComponent
{
public:
	void Initialize()override;
	void Update(float dt)override;
	void SendMessages(Message* msg)override; 

  void SerializeRead(Serializer& str) override {}
  void SerializeWrite(Serializer& str) override;

private:
	GameReactive* pReactive;
	Transform* pTransform;
	bool CurrMouseState;
	bool MouseDown;
};