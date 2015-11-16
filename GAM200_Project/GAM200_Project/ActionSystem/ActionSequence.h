#pragma once
#include "ActionBase.h"
#include <queue>

namespace ActionSystem
{
	class ActionSequence : public Internal::ActionBase
	{
	public:
		ActionSequence(bool looping = false) :
			LoopingSequence(looping),
			ActionQueue(){};
		ActionSequence(const std::deque<ActionBase*>& actionQueue, bool looping = false) :
			LoopingSequence(looping),
			ActionQueue(actionQueue){};

		//void Update(float dt) override;//stupid
		void Update(const long double& dt) override;

		bool IsEmpty()const { return ActionQueue.empty(); };
		const bool& Looping()const { return LoopingSequence; };
		bool& Looping() { return LoopingSequence; };

		void Clear();
		
		void Restart() override;

		void AddAction(ActionBase* action);
		const ActionBase& GetCurrentAction() const { return (**CurrentAction); };

		~ActionSequence() override;

	private:
		bool LoopingSequence;
		std::deque<ActionBase*>::iterator CurrentAction;
		std::deque<ActionBase*> ActionQueue;


	};
}