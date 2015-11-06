#include "ActionGroup.h"

namespace ActionSystem
{
	void ActionGroup::Update(const long double& dt)
	{
		if (IsPaused() || IsCompleted())
		{
			return;
		}

		if (IsEmpty())
		{
			Completed = true;
		}

		Completed = true;

		while (CurrentAction != ActionQueue.end())
		{
			(*CurrentAction)->Update(dt);

			if ((*CurrentAction)->IsCompleted())
			{
				CurrentAction++;
				continue;
			}

			Completed = false;
			CurrentAction++;
		}

		if (Completed)
		{
			if (Looping())
			{
				Restart();
			}
			else
			{
				Clear();
			}
		}
		CurrentAction = ActionQueue.begin();
	}

	void ActionGroup::AddAction(ActionBase* action)
	{
		ActionQueue.push_back(action);
		CurrentAction = ActionQueue.begin();
	}

	void ActionGroup::Clear()
	{
		while (!ActionQueue.empty())
		{
			delete ActionQueue.back();
			ActionQueue.pop_back();
		}
	}

	ActionGroup::~ActionGroup()
	{
		Clear();
	}
}