//#include "Collision.h"
#include "Precompiled.h"

CollisionTest CollisionRegistry[Primitive::pCount][Primitive::pCount] =
{
	{
		CircleAndCircle, CircleAndAABB
	},

	{
		AABBAndCircle, AABBAndAABB
	},
};

float CalculateRestitution(Primitive *a, Primitive *b)
{
	RigidBody* bodyA = a->GetOwner()->has(RigidBody);
	RigidBody* bodyB = b->GetOwner()->has(RigidBody);
	if (bodyA && bodyB)
	{
		return (std::min(bodyA->restitution, bodyB->restitution));
	}
	else
		return 0;
}

void CircleAndCircle(Primitive *Circle1, Primitive *Circle2, Manifold *data)
{
	// Create pointers
	//Circle *Circle1 = reinterpret_cast<Circle *>(a);
	//Circle *Circle2 = reinterpret_cast<Circle *>(b);
	Transform* trans1 = Circle1->GetOwner()->has(Transform);
	Transform* trans2 = Circle2->GetOwner()->has(Transform);

	// Calculate the vector between Circle1 and Circle2
	Vector2 midline = trans2->GetPositionXY() - trans1->GetPositionXY();

	// Calculate the distance squared
	float distSqr = midline.SqrMagnitude();

	// Calculated added radii
	float radius = Circle1->radius + Circle2->radius;

	// Case 0: No Intersection
	if (distSqr > radius * radius)
	{
		data->contactCount = 0;
		return;
	}

	float distance = sqrt(distSqr);
	// Update contact
	data->contactCount = 1;

	Vector2 normal;

	// Case 1: if circles are on top of each other
	if (distance == 0.0f)
	{
		data->penetration = Circle1->radius ;
		data->normal = Vector2(1, 0);
		data->contact[0] = trans1->GetPositionXY();
	}

	// Case 2: if circles intersects
	else
	{
		data->penetration = radius - distance;
		data->normal = midline.Normalize();
		data->contact[0] = data->normal * Circle1->radius + trans1->GetPositionXY();
	}

	// Add contact
	RigidBody* bodyA = data->A->GetOwner()->has(RigidBody);
	RigidBody* bodyB = data->B->GetOwner()->has(RigidBody);
	if (bodyA && bodyB)
	{
		bodyA = Circle1->body;
		bodyB = Circle2->body;
	}

	data->restitution = CalculateRestitution(data->A, data->B);
}

void AABBAndAABB(Primitive *a, Primitive *b, Manifold *data)
{
	//AABB *AABB1 = reinterpret_cast<AABB *>(a);
	//AABB *AABB2 = reinterpret_cast<AABB *>(b);
	Transform* transA = a->GetOwner()->has(Transform);
	Transform* transB = b->GetOwner()->has(Transform);

	// Calculate the vector between the objects
	Vector2 midline = transA->pos2d - transB->pos2d;
	printf("GetPoSxyIN COLLISION %f, %f", transA->pos2d.x, transA->pos2d.y);
	float xOverlap = (a->halfSize.x/2.0f) + (b->halfSize.x/2.0f) - fabs(midline.x);
	data->contactCount = 1;
	if (xOverlap > 0)
	{
		data->contactCount = 1;
		float yOverlap = (a->halfSize.y/2.0f) + (b->halfSize.y/2.0f) - fabs(midline.y);

		if (yOverlap > 0)
		{
			if (xOverlap < yOverlap)
			{
				Vector2 normal = midline.x < 0 ? Vector2(1, 0) : Vector2(-1, 0);
				data->A = a;
				data->B = b;
				data->normal = normal;
				data->penetration = xOverlap;
				data->restitution = CalculateRestitution(a, b);
				AABB * shapeA = a->GetOwner()->has(AABB);
				//data->contact[0] = data->normal * shapeA->halfSize.x + transA->GetPositionXY();
				return;
			}
			else
			{
				Vector2 normal = midline.y < 0 ? Vector2(0, 1) : Vector2(0, -1);
				data->A = a;
				data->B = b;
				data->normal = normal;
				data->penetration = yOverlap;
				data->restitution = CalculateRestitution(a, b);
				AABB * shapeB = b->GetOwner()->has(AABB)
				//data->contact[0] = data->normal * shapeB->halfSize.y + transB->GetPositionXY();
				return;
			}
		}
	}
	// No Collision
	data->contactCount = 0;

}

void AABBAndCircle(Primitive *shapeAABB, Primitive *shapeCircle, Manifold *data)
{
	/*AABB *aabb;
	Circle *circle;
	// Create pointers based on what is what
	if (a->GetID() == Primitive::pCircle)
	{
		aabb = reinterpret_cast<AABB *>(b->bodyShape);
		circle = reinterpret_cast<Circle *>(a->bodyShape);
	}
	else
	{
		aabb = reinterpret_cast<AABB *>(a->bodyShape);
		circle = reinterpret_cast<Circle *>(b->bodyShape);
	}*/
	Transform* transAABB = shapeAABB->GetOwner()->has(Transform);
	Transform* transCircle = shapeCircle->GetOwner()->has(Transform);

	//  Calculate the vector between the objects
	Vector2 midline = transCircle->GetPositionXY() - transAABB->GetPositionXY();
	//printf("CirclePos: %f, %f", transCircle->GetPositionXY().x, transCircle->GetPositionXY().y);
	// Closest point on A to the center of B
	Vector2 closest = midline;

	// Calculate half extent for each axis
	float x_extent = shapeAABB->halfSize.x /2.0f;
	float y_extent = shapeAABB->halfSize.y /2.0f;

	// Clamp t0=o point to edges of AABB
	closest.x = Clamp(-x_extent, x_extent, closest.x);
	closest.y = Clamp(-y_extent, y_extent, closest.y);

	bool inside = false;

	// If circle is inside, clamp the circle's center to the closest
	// AABB's edge

	if (midline == closest)
	{
		inside = true;

		// Find the closest AABB's axis
		if (abs(midline.x) > abs(midline.y))
		{
			// Clamp to the closest extent
			if (closest.x > 0)
				closest.x = x_extent;
			else
				closest.x = -x_extent;
		}
		// y axis is shorter
		else
		{
			// Clamp to closest extent
			if (closest.y > 0)
				closest.y = y_extent;
			else
				closest.y = -y_extent;
		}
	}

	Vector2 normal = midline - closest;
	float distance = normal.Magnitude();
	float radius = shapeCircle->radius;

	// Circle not inside the AABB
	if (distance > radius * radius && !inside)
	{
		data->contactCount = 0;
		return;
	}

	distance = sqrtf(distance);

	// If circle is inside AABB,
	// Collision normal flipped to point outside
	if (inside)
	{
		data->normal = -midline;
		data->penetration = radius - distance /2.0f;
		data->restitution = CalculateRestitution(shapeAABB , shapeCircle);
	}
	else
	{
		data->normal = midline;
		data->penetration = radius - distance /2.0f;
		data->restitution = CalculateRestitution(shapeAABB, shapeCircle);
	}

	// Update contact
	data->contactCount = 1;
	data->A = shapeAABB;
	data->B = shapeCircle;
}

void CircleAndAABB(Primitive *b, Primitive *a, Manifold *data)
{
	AABBAndCircle(a, b, data);
}

float Clamp(float min, float max, float x)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	return x;
}
