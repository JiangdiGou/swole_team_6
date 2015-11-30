#pragma once

#include "../Component.h"

class PlayerTag : public GameComponent
{
public:
	void Initialize()override;
    void SerializeWrite(Serializer& str) override;
};