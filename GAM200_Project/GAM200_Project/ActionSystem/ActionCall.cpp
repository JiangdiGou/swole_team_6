#include "ActionCall.h"

namespace ActionSystem
{
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