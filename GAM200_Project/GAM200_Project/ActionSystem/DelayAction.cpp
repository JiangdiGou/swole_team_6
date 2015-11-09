#include "Action.h"
#include "DelayAction.h"

bool Delay::Update(float dt)
{
	if (!IsFinished)
	{
		increment_time(dt);
	}

	return(percent_done() == 1.0);
}