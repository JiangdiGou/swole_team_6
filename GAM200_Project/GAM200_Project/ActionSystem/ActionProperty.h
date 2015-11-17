#pragma once
#include "ActionBase.h"
#include "SampleCurve.h"
#include <functional>

namespace ActionSystem
{
	template <typename T>
	class ActionProperty : public Internal::ActionBase
	{
	public:
		ActionProperty(T* startVal, const T7 endVal, const long double& duration, const Ease&.ease) :
			StartVal(*startVal), EndVal(envVal), CurrentVal(startVal), EndTime(duration),
			EasingCurve(ease)
		{
		}

		void Restart() override
		{
			ActionBase::Restart();
			CurrentTime = 0;
			StartVal = *CurrentVal;
		}

		void Restart(const T& startVal)
		{
			*CurrentVal = startVal;
			Restart();
		}

		void Restart(T* startVal)
		{
			CurrentVal = startVal;
			Restart(*startVal);
		}

		const T& EndValue() const { return EndVal; }

		T& EndValue() { return EndVal; }

		const long double& TimeElapsed() const { return CurrentTime; }

		long double& TimeElapsed() { return CurrentTime; }

		const long double& Duration() const { return EndTime; }

		void ActionUpdate(const long double& dt) override
		{
			//See if this action is paused or completed
			if (IsPause() || IsCompleted())
			{
				return;
			}

			//Gets the changed value using curves from the action math library
			*CurrentVal = EasingCurve.Sample(CurrentTime, StartVal, EndVal, EndTime);

			//Increment the time on this action
			CurrentTime += dt;

			//Check for completed action
			if (CurrentTime >= EndTime)
			{
				*CurrentVal = EndVal;
				CurrentTime = EndTime;
				Completed = true;
			}
		}

	private:
		T StartVal;
		T EndVal;
		T* CurrentVal;

		long double CurrentTime = 0;
		long double EndTime;

		SampleCurve<T> EaseingCurve;
	};

}