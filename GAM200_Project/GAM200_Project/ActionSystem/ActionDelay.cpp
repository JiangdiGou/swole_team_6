#include "ActionDelay.h"

namespace ActionSystem
{
	void ActionDelay::Update(const long double& dt)
	{
		if (IsCompleted() || IsPaused())
		{
			return;
		}

		CurrentTime += dt;

		if (CurrentTime >= EndTime)
		{
			Completed = true;
		}
	}
}