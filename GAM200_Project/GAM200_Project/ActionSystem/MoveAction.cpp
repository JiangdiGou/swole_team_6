#include "Action.h"
#include "MoveAction.h"


bool Move::Update(float dt)
{
	//increment time on the action
	increment_time(dt);

	//if the action is not yet done
	if (!IsFinished)
	{
		//perform the action
		if (!blocking)
		{
			if (FirstTime)
			{
				object.Position = StartPos;
			}
			else
			{
				object.Position = StartPos + (FinalPos - StartPos);
			}
		}
		else
			return;
	}

	return(percent_done() == 1.0);
}
