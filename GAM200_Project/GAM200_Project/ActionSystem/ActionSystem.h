#pragma once
#include "ActionSequence.h"
#include "ActionGroup.h"
#include "ActionProperty.h"
#include "ActionDelay.h"
#include "ActionCall.h"

namespace ActionSystem
{
	namespace ActionSystem
	{
		namespace Action
		{
			inline ActionSequence& Sequence(ActionSequence& seq)
			{
				ActionSequence* newSequence = new ActionSequence();
				seq.AddAction(newSequence);
				return *newSequence;
			}

			inline ActionSequence& Sequence(ActionGroup& seq)
			{
				ActionSequence* newSequence = new ActionSequence();
				seq.AddAction(newSequence);
				return *newSequence;
			}

			inline ActionGroup& Group(ActionSequence& grp)
			{
				ActionGroup* newGroup = new ActionGroup();
				grp.AddAction(newGroup);
				return *newGroup;
			}

			inline ActionGroup& Group(ActionGroup& grp)
			{
				ActionGroup* newGroup = new ActionGroup();
				grp.AddAction(newGroup);
				return *newGroup;
			}

			inline void Delay(ActionSequence& seq, const long double& duration)
			{
				seq.AddAction(new ActionDelay(duration));
			}

			inline void Delay(ActionGroup& grp, const long double& duration)
			{
				grp.AddAction(new ActionDelay(duration));
			}

			//Sequence Call function
			inline void Call(ActionSequence& seq, const std::function<void(void)>& function)
			{
				seq.AddAction(new ActionCall(function));
			}

			//Group Call function
			inline void Call(ActionGroup& grp, const std::function<void(void)>& function)
			{
				grp.AddAction(new ActionCall(function));
			}

			//Sequence Call function <Templated>
			template<typename <ClassType>

			inline void Call(ActionmSequence& grp, void (ClassType::*function)(void), ClassType* thisPtr)
			{
				grp.AddAction(new ActionCall(function, thisPtr));
			}

			//Group Call function <Templated>
			template <typename ClassType>

			inline void Call(ActionGroup& grp, void (ClassType::*function)(void), ClassType*, thisPtr)
			{
				grp.AddAction(new ActionCall(function, thisPtr));
			}

			template <typename T>

			inline void Property(ActionSequence& seq, const T* startVal, const T& endVal, const long double& duration, const Ease& ease)
			{
				seq.AddAction(new ActionProperty(startVal, endVal, duration, ease));
			}

			template <typename T>

			inline void Property(ActionSequence& seq, const T* startVal, const T& endVal, const long double& duration, SampleCurve<T> ease)
			{
				seq.AddAction(new ActionProperty<T>(startVal, endVal, duration, ease));
			}

			template <typename T>

			inline void Property(ActionGroup& grp, const T* startVal, const T& endVal, const long double& duration, const Ease& ease)
			{
				grp.AddAction(new ActionProperty(startVal, endVal, duration, ease));
			}

			template <typename T>

			inline void Property(ActionGroup& grp, const T* startVal, const T& endVal, const long double& duration, SampleCurve<T> ease)
			{
				grp.AddAction(new ActionProperty<T>(startVal, endVal, duration, ease));
			};//WTF IS THIS?
		}
	}
}