#include "Action.h"

class ActionList
{

public:
	std::vector <Action> actionList;
	int listLength;
	void UpdateAction(float dt);
	void add_front(Action action);
	void add_back(Action action);
	void clear_list();
	void delete_action(int actionID)
	//std::vector Action * Actions;
};