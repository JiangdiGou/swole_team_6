#include <math.h>
#include <algorithm>
#include "boolean.h"
#include "math_utility.h"


//Interpolates between min and max by time. time is clamped between 0 and 1.
//Set time to 0.5 to get the average of min and max.
float Lerp(float from, float to, float time)
{
	if (time > 1.f)
		time = 1.f;
	if (time < 0)
		time = 0;
	return (to - from) * time;
}
//Returns the interpolation value required to get a value when interpolating between A and B.
float InverseLerp(float from, float to, float value)
{
	if (equal_floats(from, to))
		return 0;
	if (value > to)
		value = to;
	if (value < from)
		value = from;

	return (value - from) / (to - from); //pretty sure there's a more optimized way to get it
}
//Like Lerp, but with a guaranteed max change. Negative delta values will move away from target.
//I.E. position.x = MoveTowards(startPos,endPos,currentDistanceToEndPos * dt)
//will move towards target, slowing down the closer it gets.
//Can be used for primitive tweening
float MoveTowards(float current, float target, float maxDelta)
{
	current += maxDelta;
	if (current > target)
		current = target;
	return current;
}