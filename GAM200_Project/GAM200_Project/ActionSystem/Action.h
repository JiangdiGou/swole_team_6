#ifndef ACTION_H
#define ACTION_H

#include <vector>
#include <list>
#include "action_math_utility.h"

class Action
{
public:
	char sequence;
	float duration;
	float timeLeft;
	bool blocking;
	int ID;
	bool IsFinished;
	bool FirstTime;
	std::vector <bool> flags;

	bool Update(float dt);
	void increment_time(float dt);
	float percent_done();
};

#endif