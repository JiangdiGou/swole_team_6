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

  Vector3 getOffset() { return offset; }
  void setOffset(Vector3 newOffset) { offset = newOffset;  }

	HUDcomponent();

private:
	Transform* pTransform;
	Transform* camPos;
	Vector3D offset;
	bool CurrMouseState;
	bool MouseDown;
};