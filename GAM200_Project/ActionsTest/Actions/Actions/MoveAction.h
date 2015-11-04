#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "Action.h"

class Move : public Action
{
public:
	virtual bool Update(float dt);

private:
	Vector3D StartPos;
	Vector3D FinalPos;
};

#endif