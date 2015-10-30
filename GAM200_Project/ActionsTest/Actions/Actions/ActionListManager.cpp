#include "ActionListManager.h"

void ActionListManager::Update(float dt)
{
	for (std::vector<ActionList>::iterator it = actionListManager.begin(); it != actionListManager.end(); it++)
	{
		(*it).UpdateAction(dt);
	}
}