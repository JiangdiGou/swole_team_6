#include "ActionDelay.h"

namespace ActionSystem
{
	void ActionDelay::Update(float dt)
	{
		float* doubDt = &dt;
		ActionUpdate((const long double&)doubDt);
	}

	void ActionDelay::ActionUpdate(const long double& dt)
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