/******************************************************************************/
/*!
\author Mitch Regan

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once

#include "../Component.h"

class PlayerTag : public GameComponent
{
public:
	void Initialize()override;
    void SerializeWrite(Serializer& str) override;
};