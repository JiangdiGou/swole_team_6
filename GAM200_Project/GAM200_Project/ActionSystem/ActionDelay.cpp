#include "ActionDelay.h"

namespace ActionSystem
{
	void ActionDelay::Update(float dt)
	{
		float* doubDt = &dt;
		Update((const long double&)doubDt);
	}

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