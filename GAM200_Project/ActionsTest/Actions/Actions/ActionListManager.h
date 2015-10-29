#include "ActionList.h"

class ActionListManager : public ISystem
{
public:
	std::vector <ActionList> actionListManager;
	int listLength;
	void Update(float dt) override;

	//std::vector Action * Actions;
};