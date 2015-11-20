#pragma once
#include "ActionBase.h"
#include <deque>

namespace ActionSystem
{
	class ActionGroup : public ActionBase
	{
	public:
		ActionGroup(bool looping = false) :
			LoopingSequence(looping),
			ActionQueue(){};
		ActionGroup(const std::deque<ActionBase*>& actionQueue, bool looping = false) :
			LoopingSequence(looping),
			ActionQueue(actionQueue){};


		void Update(float dt) override;//stupid

		void ActionUpdate(const long double& dt) override;

		bool IsEmpty()const { return ActionQueue.empty(); };
		const bool& Looping()const { return LoopingSequence; };
		bool& Looping() { return LoopingSequence; };

		void Clear();

		void Restart() override;

		void AddAction(ActionBase* action);

		~ActionGroup() override;
	private:
		//Looping groups do not clear when completed
		bool LoopingSequence;
		std::deque<ActionBase*>::iterator CurrentAction;
		std::deque<ActionBase*> ActionQueue;

	};
}