#include "ActionSequence.h"

namespace ActionSystem
{
	void ActionSequence::Update(const long double& dt)
	{
		if (IsPaused() || IsCompleted())
		{
			return;
		}
		if (IsEmpty())
		{
			Completed = true;
			return;
		}

		if ((*CurrentAction)->IsCompleted())
		{
			//If the actiong sequence is not looping
			if (!Looping())
			{
				delete (*CurrentAction);
				ActionQueue.erase(CurrentAction);
				CurrentAction = ActionQueue.begin();

				if (ActionQueue.empty())
				{
					Completed = true;
					return;
				}
			}
			//If the action sequence is looping
			else
			{
				CurrentAction++;

				if (CurrentAction == ActionQueue.end())
				{
					//Reset the sequence
					CurrentAction = ActionQueue.begin();
				}

				(*CurrentAction)->Restart();
			}

			(*CurrentAction)->Update(dt);
		}
	}

	void ActionSequence::AddAction(ActionBase* action)
	{
		ActionQueue.push_back(action);
		CurrentAction = ActionQueue.begin();
	}

	void ActionSequence::Clear()
	{
		while (!ActionQueue.back())
		{
			ActionQueue.pop_back();
		}

		Restart();
	}

	ActionSequence::~ActionSequence()
	{
		Clear();
	}
}