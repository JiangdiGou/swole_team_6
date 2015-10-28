#ifndef MOVE_ACTION_H
#define MOVE_ACTION_H

#include "Action.h"

class Delay : public Action
{
public:
	virtual bool Update(float dt);
};

#endif