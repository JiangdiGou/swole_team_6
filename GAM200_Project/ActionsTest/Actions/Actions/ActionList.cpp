#include "ActionList.h"

void ActionList::UpdateAction(float dt)
{
	//iterate through the entire vector
	for (std::vector<Action>::iterator it = actionList.begin(); it  != actionList.end(); it++)
	{
		(*it).Update(dt);
	}
}

void ActionList::add_front(Action action)
{
	actionList.insert(actionList.begin() , action);
}

void ActionList::add_back(Action action)
{
	actionList.insert(actionList.end(), action);
}

void ActionList::delete_action(int actionID)
{
	for (std::vector<Action>::iterator it = actionList.begin(); it != actionList.end(); it++)
	{
		if ((*it).ID == actionID)
		{
			actionList.erase(it);
		}
	}
}

void ActionList::clear_list()
{
	for (std::vector<Action>::iterator it = actionList.begin(); it != actionList.end(); it++)
	{
		actionList.clear();
	}
}
