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

	if (aPosition.y + a->halfSize.y/2.0f <= bPosition.y - b->halfSize.y/2.0f ||
		bPosition.y + b->halfSize.y/2.0f <= aPosition.y - a->halfSize.y/2.0f ||
		aPosition.x + a->halfSize.x/2.0f <= bPosition.x - b->halfSize.x/2.0f ||
		bPosition.x + b->halfSize.x/2.0f <= aPosition.x - a->halfSize.x/2.0f)
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
	if (circle.x > box.x + a->halfSize.x/2.0f )
	{
		point.x = box.x + a->halfSize.x /2.0f;
	}
	else if (circle.x < box.x - a->halfSize.x /2.0f)
	{
		point.x = box.x - a->halfSize.x/2.0f ;
	}

	// y-axis
	if (circle.y  > box.y + a->halfSize.y /2.0f )
	{
		point.y = box.y + a->halfSize.y /2.0f;
	}
	else if (circle.y < box.y - a->halfSize.y /2.0f)
	{
		point.y = box.y - a->halfSize.y /2.0f;
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
		point.x = box.x + b->halfSize.x;
	}
	else if (circle.x < box.x - b->halfSize.x)
	{
		point.x = box.x - b->halfSize.x;
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
