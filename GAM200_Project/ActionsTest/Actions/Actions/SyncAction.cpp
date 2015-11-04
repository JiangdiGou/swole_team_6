#include "Action.h"
#include "SyncAction.h"


bool Sync::Update(float dt)
{
	increment_time(dt);

	if (!IsFinished)
	{
		
	}

	return(percent_done() == 1.0);
}
