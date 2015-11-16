#include "ActionCall.h"

namespace ActionSystem
{
	void ActionCall::Update(float dt)
	{
		float* doubDt = &dt;
		Update((const long double&)doubDt);
	}

	void ActionCall::Update(const long double& dt)
	{
		if (IsCompleted() || IsPaused())
		{
			return;
		}

		Function();

		Completed = true;
	}
}