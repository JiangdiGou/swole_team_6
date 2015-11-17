#pragma once
#include "ActionBase.h"
#include <deque>

namespace ActionSystem
{
	class ActionDelay : public Internal::ActionBase
	{

	public:
		ActionDelay(const long double& duration = 0) : EndTime(duration){};

		void ActionUpdate(const long double& dt) override;

		void Update(float dt) override;//stupid

		const long double& Duration() const { return EndTime; }

		long double& Duration() { return EndTime; }

		void Restart() override { ActionBase::Restart(); CurrentTime = 0; };

		void Restart(const long double& duration) { EndTime = duration; Restart(); }


	private:
		long double CurrentTime = 0;

		long double EndTime;
	};
}