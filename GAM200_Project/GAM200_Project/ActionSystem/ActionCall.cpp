#include "ActionCall.h"

namespace ActionSystem
{
	void ActionCall::Update(float dt)
	{
		float* doubDt = &dt;
		ActionUpdate((const long double&)doubDt);
	}

	void ActionCall::ActionUpdate(const long double& dt)
	{
		if (IsCompleted() || IsPaused())
		{
			return;
		}

		Function();

		Completed = true;
	}
}