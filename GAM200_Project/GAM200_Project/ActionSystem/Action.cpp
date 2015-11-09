#include "Action.h"

//seq, @property, new property, duration, interpolation
bool Action::Update(float dt)
{
	//increment time on the action
	increment_time(dt);

	//if the action is not yet done
	if (!IsFinished)
	{
		//perform the action
		if (!blocking)
		{

		}
		else
			return;
	}
		
	return(percent_done() == 1.0);
}

void Action::increment_time(float dt)
{
	float dt = 0.0167;
	timeLeft -= dt;
}

float Action::percent_done()
{
	float percentDone = 0.0;

	//gets the percentage of time the left on a given action
	percentDone = timeLeft / duration;

	return percentDone;
}
