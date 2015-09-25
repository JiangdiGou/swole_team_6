#include "CollisionCheck.h"
#include "Precompiled.h"

bool CollisionChecker::CircleAndCircle(Circle *a, Vector3 aPos, Circle *b, Vector3 bPos)
{
	// Calculate the distance between centre points of two Circle
	Vector3 aPosition = aPos;
	Vector3 bPosition = bPos;
	float distance = Vector3::Distance(aPosition, bPosition);


	if (distance <= a->radius * b->radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CollisionChecker::AABBAndAABB(AABB *a, Vector3 aPos, AABB *b, Vector3 bPos)
{
	Vector3 aPosition = aPos;
	Vector3 bPosition = bPos;

	if (aPosition.y + a->halfSize.y <= bPosition.y - b->halfSize.y ||
		bPosition.y + b->halfSize.y <= aPosition.y - a->halfSize.y ||
		aPosition.x + a->halfSize.x <= bPosition.x - b->halfSize.x ||
		bPosition.x + b->halfSize.x <= aPosition.x - a->halfSize.x)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CollisionChecker::AABBAndCircle(AABB *a, Vector3 aPos, Circle *b, Vector3 bPos)
{
	Vector3 box = aPos;
	Vector3 circle = bPos;
	Vector3 point;
	point.x = bPos.x;
	point.y = bPos.y;

	// x-axis
	if (circle.x > box.x + a->halfSize.x)
	{
		point.x = circle.x + a->halfSize.x;
	}
	else if (circle.x < box.x - a->halfSize.x)
	{
		point.x = circle.x - a->halfSize.x;
	}

	// y-axis
	if (circle.y  > box.y + a->halfSize.y)
	{
		point.y = box.y + a->halfSize.y;
	}
	else if (circle.y < box.y - a->halfSize.y)
	{
		point.y = box.y - a->halfSize.y;
	}

	float distance = Vector3::Distance(circle, point);

	if (distance >= b->radius * b->radius)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool CollisionChecker::CircleAndAABB(Circle *a, Vector3 aPos, AABB *b, Vector3 bPos)
{
	Vector3 box = bPos;
	Vector3 circle = aPos;
	Vector3 point;
	point.x = aPos.x;
	point.y = aPos.y;

	// x-axis
	if (circle.x > box.x + b->halfSize.x)
	{
		point.x = circle.x + b->halfSize.x;
	}
	else if (circle.x < box.x - b->halfSize.x)
	{
		point.x = circle.x - b->halfSize.x;
	}

	// y-axis
	if (circle.y  > box.y + b->halfSize.y)
	{
		point.y = box.y + b->halfSize.y;
	}
	else if (circle.y < box.y - b->halfSize.y)
	{
		point.y = box.y - b->halfSize.y;
	}

	float distance = Vector3::Distance(circle, point);

	if (distance >= a->radius * a->radius)
	{
		return false;
	}
	else
	{
		return true;
	}


}
