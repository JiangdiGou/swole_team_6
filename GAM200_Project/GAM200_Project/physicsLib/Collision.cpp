#include "Collision.h"
//#include "Precompiled.h"
#include "PhysicsManager.h"
#include "Transform.h"

//sample

float DetermineRestitution(Body * a, Body * b)
{
	return 	std::min(a->Restitution, b->Restitution);
}

float DetermineFriction(Body * a, Body * b)
{
	return sqrt(a->Friction*b->Friction);
}

void ShapeCircle::Draw()
{
	/*Drawer::Instance.DrawCircle(body->Position, Radius);*/
}

bool ShapeCircle::TestPoint(Vec2D testPoint)
{
	//Vec2D delta = body->Position - testPoint;
	//float dis = Normalize(delta);
	//if (dis < Radius)
	//	return true;
	//else
	return false;
}

void ShapeAAB::Initialize()
{
  /*body = GetOwner()->has(Body);
  if (body == NULL)
    return;
  body->BodyShape = this;*/
}

void ShapeAAB::Draw()
{


	//debugDrawSquare(ownerTrans->GetPosition(), Extents.x, Extents.y, Vector3(0, 0, 0));
}

bool ShapeAAB::TestPoint(Vec2D testPoint)
{
	Vec2D delta = body->Position - testPoint;
	if (fabs(delta.x) < Extents.x)
	{
		if (fabs(delta.y) < Extents.y)
		{
			return true;
		}
	}
	return false;
}


float Clamp(float min, float max, float x)
{
	if (x < min)
		return min;
	else if (x > max)
		return max;
	return x;
}
/////////////////////Collsion Detection Functions////////////////////

bool line_rectangle_collide( Vec2D startBase, Vec2D endDirection)
{
	Shape* a;
	Shape* b;
	ShapeLine * LineA = (ShapeLine*)a;
	ShapeAAB * boxB = (ShapeAAB*)b;

	GOC* bowner = b->GetOwner();
	Transform* aTrans = a->GetOwner()->has(Transform);
	Transform* bTrans = b->GetOwner()->has(Transform);
	startBase = aTrans->GetPositionXY();
	endDirection = bTrans->GetPositionXY();

	//ShapeAAB * Box = (ShapeAAB*)endDirection;

	//GOC* bowner = r->GetOwner();
	//Transform* aTrans = l->GetOwner()->has(Transform);
	//Transform* bTrans = r->GetOwner()->has(Transform);
	//at = aTrans->GetPositionXY();
	//bt = bTrans->GetPositionXY();
	////Check X
	//Vec2D positionDelta = at - bt;




    Vec2D n = Vec2D::rotate_vector_90(&endDirection);

	float dp1, dp2, dp3, dp4;

	Vec2D c1 = boxB->origin;
	Vec2D c2 = Vec2D::add_vector(&c1, &boxB->Extents);
	Vec2D c3 = { c2.x, c1.y };
	Vec2D c4 = { c1.x, c2.y };

	c1 = Vec2D::subtract_vector(&c1, &startBase);
	c2 = Vec2D::subtract_vector(&c2, &startBase);
	c3 = Vec2D::subtract_vector(&c3, &startBase);
	c4 = Vec2D::subtract_vector(&c4, &startBase);

	dp1 = Vec2D::DotProduct(n, c1);
	dp2 = Vec2D::DotProduct(n, c2);
	dp3 = Vec2D::DotProduct(n, c3);
	dp4 = Vec2D::DotProduct(n, c4);

	//return (dp1 * dp2 <= 0) || (dp2 * dp3 <= 0) || (dp3 * dp4 <= 0);
	if ((dp1 * dp2 <= 0) || (dp2 * dp3 <= 0) || (dp3 * dp4 <= 0))
	{
		//ManifoldSet * contact = c->GetNewContact();
		//contact->Bodies[0] = Line->body;
		//contact->Bodies[1] = Box->body;
		//contact->ContactNormal = positionDelta;//A to B
		//contact->Penetration = 0.0f;
		//contact->Restitution = DetermineRestitution(l->body, r->body);
		//contact->FrictionCof = DetermineFriction(l->body, r->body);
		printf("Slash Slash Slash !!!!");
		return true;
	}
	else
		return false;


}

bool DetectCollisionCircleCircle(Shape*a, Vec2D at, Shape*b, Vec2D bt, contactList*c)
{
	ShapeCircle * spA = (ShapeCircle*)a;
	ShapeCircle * spB = (ShapeCircle*)b;

	Vec2D positionDelta = at - bt;
	float disSquared = positionDelta.SqrMagnitude();
	float combinedRadius = spA->Radius + spB->Radius;

	//Is the squared distance between the two sphere less
	//then the squared radius?
	if (disSquared < combinedRadius*combinedRadius)
	{
		//Get not squared values

		Vec2D normal;
		float penetration;
		if (disSquared == 0.0f)
		{
			//Right on top of each other
			penetration = spA->Radius;
			normal = Vec2D(1, 0);
		}
		else
		{
			float dis = positionDelta.NormalizeNew(positionDelta);
			penetration = combinedRadius - dis;
			normal = positionDelta;
		}

		//Add a contact
		ManifoldSet * contact = c->GetNewContact();
		contact->Bodies[0] = spA->body;
		contact->Bodies[1] = spB->body;
		contact->ContactNormal = positionDelta;//A to B
		contact->Penetration = penetration;
		contact->Restitution = DetermineRestitution(a->body, b->body);
		contact->FrictionCof = DetermineFriction(a->body, b->body);
		return true;
	}
	else
		return false;


	return false;
}

bool  DetectCollisionCircleAABox(Shape*a, Vec2D at, Shape*b, Vec2D bt, contactList*c)
{
	//ShapeCircle * spA = (ShapeCircle*)a;
	//ShapeAAB * boxB = (ShapeAAB*)b;

	//float radius = spA->Radius;
	//Vec2D p = at;
	//Vec2D minV(bt.x - boxB->Extents.x, bt.y - boxB->Extents.y);
	//Vec2D maxV(bt.x + boxB->Extents.x, bt.y + boxB->Extents.y);

	//Vec2D q;
	//for (int i = 0; i < 2; ++i)
	//{
	//	float v = p[i];
	//	if (v < minV[i]) v = minV[i];
	//	if (v > maxV[i]) v = maxV[i];
	//	q[i] = v;
	//}

	//Vec2D delta = p - q;
	//float disSq = delta.SqrMagnitude();
	//if (disSq < radius * radius)
	//{
	//	if (disSq == 0.0f)
	//	{
	//		//internal
	//		Vec2D bdelta = at - bt;

	//		float xd = radius + boxB->Extents.x - fabs(bdelta.x);
	//		float yd = radius + boxB->Extents.y - fabs(bdelta.y);

	//		Vec2D normal;
	//		float penetration;

	//		if (xd < yd)
	//		{
	//			normal = bdelta.x < 0 ? Vec2D(-1, 0) : Vec2D(1, 0);
	//			penetration = xd;
	//		}
	//		else
	//		{
	//			normal = bdelta.y < 0 ? Vec2D(0, -1) : Vec2D(0, 1);
	//			penetration = yd;
	//		}

	//		ManifoldSet * contact = c->GetNewContact();
	//		contact->Bodies[0] = spA->body;
	//		contact->Bodies[1] = boxB->body;
	//		contact->ContactNormal = normal;
	//		contact->Penetration = penetration;
	//		contact->Restitution = DetermineRestitution(a->body, b->body);
	//		contact->FrictionCof = DetermineFriction(a->body, b->body);
	//	}
	//	else
	//	{
	//		float dis = delta.NormalizeNew(delta);
	//		ManifoldSet * contact = c->GetNewContact();
	//		contact->Bodies[0] = spA->body;
	//		contact->Bodies[1] = boxB->body;
	//		contact->ContactNormal = delta;
	//		contact->Penetration = -(dis - spA->Radius);
	//		contact->Restitution = DetermineRestitution(a->body, b->body);
	//		contact->FrictionCof = DetermineFriction(a->body, b->body);
	//	}
	//}
	return false;
}

bool  DetectCollisionAABoxAABox(Shape*a, Vec2D at, Shape*b, Vec2D bt, contactList*c)
{
	ShapeAAB * boxA = (ShapeAAB*)a;
  ShapeAAB * boxB = (ShapeAAB*)b;

  GOC* bowner = b->GetOwner();
  Transform* aTrans = a->GetOwner()->has(Transform);
  Transform* bTrans = b->GetOwner()->has(Transform);
  at = aTrans->GetPositionXY();
  bt = bTrans->GetPositionXY();
	//Check X
	Vec2D positionDelta = at - bt;
	float xDiff = boxA->Extents.x + boxB->Extents.x - fabs(positionDelta.x);

	//Boxes overlapping on x-axis?
	if (0 < xDiff)
	{
		float yDiff = boxA->Extents.y + boxB->Extents.y - fabs(positionDelta.y);

		//Boxes overlapping on y-axis?
		if (0 < yDiff)
		{
			//Which axis is overlapping less? that is the axis we want
			//to use for the collision.
			if (xDiff < yDiff)
			{
				//X is smallest
				ManifoldSet * contact = c->GetNewContact();
				Vec2D normal = positionDelta.x < 0 ? Vec2D(-1, 0) : Vec2D(1, 0);
				contact->Bodies[0] = boxA->body;
				contact->Bodies[1] = boxB->body;
				contact->ContactNormal = normal;
				contact->Penetration = xDiff;
				contact->Restitution = DetermineRestitution(a->body, b->body);
				contact->FrictionCof = DetermineFriction(a->body, b->body);
				return true;
			}
			else
			{
				//Y is smallest
				ManifoldSet * contact = c->GetNewContact();
				Vec2D normal = positionDelta.y < 0 ? Vec2D(0, 1) : Vec2D(0, -1);
				contact->Bodies[1] = boxA->body;
				contact->Bodies[0] = boxB->body;
				contact->ContactNormal = normal;
				contact->Penetration = yDiff;
				contact->Restitution = DetermineRestitution(a->body, b->body);
				contact->FrictionCof = DetermineFriction(a->body, b->body);
				return true;
			}
		}
	}
	return false;
}


//Auxiliary
bool  DetectCollisionBoxCircle(Shape*a, Vec2D at, Shape*b, Vec2D bt, contactList*c)
{
	return DetectCollisionCircleAABox(b, bt, a, at, c);
}


CollsionDatabase::CollsionDatabase()
{
	//Register collision tests for all the shape types
	RegisterCollsionTest(Shape::SidCircle, Shape::SidCircle, DetectCollisionCircleCircle);
	RegisterCollsionTest(Shape::SidBox, Shape::SidBox, DetectCollisionAABoxAABox);
	RegisterCollsionTest(Shape::SidCircle, Shape::SidBox, DetectCollisionCircleAABox);
	RegisterCollsionTest(Shape::SidBox, Shape::SidCircle, DetectCollisionBoxCircle);
	//RegisterCollsionTest(Shape::SidLine, Shape::SidBox, line_rectangle_collide);
}

void CollsionDatabase::RegisterCollsionTest(Shape::ShapeId a, Shape::ShapeId b, CollisionTest test)
{
	CollsionRegistry[a][b] = test;
}

bool CollsionDatabase::GenerateContacts(Shape* shapeA, Vec2D poistionA, Shape* shapeB, Vec2D poistionB, contactList*c)
{
	return (*CollsionRegistry[shapeA->Id][shapeB->Id])(shapeA, poistionA, shapeB, poistionB, c);
}



//CollisionTest CollisionRegistry[Primitive::pCount][Primitive::pCount] =
//{
//	{
//		CircleAndCircle, CircleAndAABB
//	},
//
//	{
//		AABBAndCircle, AABBAndAABB
//	},
//};
//
//float CalculateRestitution(Primitive *a, Primitive *b)
//{
//	RigidBody* bodyA = a->GetOwner()->has(RigidBody);
//	RigidBody* bodyB = b->GetOwner()->has(RigidBody);
//	if (bodyA && bodyB)
//	{
//		return (std::min(bodyA->restitution, bodyB->restitution));
//	}
//	else
//		return 0;
//}
//
//void CircleAndCircle(Primitive *Circle1, Primitive *Circle2, Manifold *data)
//{
//	// Create pointers
//	//Circle *Circle1 = reinterpret_cast<Circle *>(a);
//	//Circle *Circle2 = reinterpret_cast<Circle *>(b);
//	Transform* trans1 = Circle1->GetOwner()->has(Transform);
//	Transform* trans2 = Circle2->GetOwner()->has(Transform);
//
//	// Calculate the vector between Circle1 and Circle2
//	Vector2 midline = trans2->GetPositionXY() - trans1->GetPositionXY();
//
//	// Calculate the distance squared
//	float distSqr = midline.SqrMagnitude();
//
//	// Calculated added radii
//	float radius = Circle1->radius + Circle2->radius;
//
//	// Case 0: No Intersection
//	if (distSqr > radius * radius)
//	{
//		data->contactCount = 0;
//		return;
//	}
//
//	float distance = sqrt(distSqr);
//	// Update contact
//	data->contactCount = 1;
//
//	Vector2 normal;
//
//	// Case 1: if circles are on top of each other
//	if (distance == 0.0f)
//	{
//		data->penetration = Circle1->radius ;
//		data->normal = Vector2(1, 0);
//		data->contact[0] = trans1->GetPositionXY();
//	}
//
//	// Case 2: if circles intersects
//	else
//	{
//		data->penetration = radius - distance;
//		data->normal = midline.Normalize();
//		data->contact[0] = data->normal * Circle1->radius + trans1->GetPositionXY();
//	}
//
//	// Add contact
//	RigidBody* bodyA = data->A->GetOwner()->has(RigidBody);
//	RigidBody* bodyB = data->B->GetOwner()->has(RigidBody);
//	if (bodyA && bodyB)
//	{
//		bodyA = Circle1->body;
//		bodyB = Circle2->body;
//	}
//
//	data->restitution = CalculateRestitution(data->A, data->B);
//}
//
//void AABBAndAABB(Primitive *a, Primitive *b, Manifold *data)
//{
//	//AABB *AABB1 = reinterpret_cast<AABB *>(a);
//	//AABB *AABB2 = reinterpret_cast<AABB *>(b);
//	Transform* transA = a->GetOwner()->has(Transform);
//	Transform* transB = b->GetOwner()->has(Transform);
//
//	// Calculate the vector between the objects
//	Vector2 midline = transA->pos2d - transB->pos2d;
//	printf("GetPoSxyIN COLLISION %f, %f", transA->pos2d.x, transA->pos2d.y);
//	float xOverlap = (a->halfSize.x/2.0f) + (b->halfSize.x/2.0f) - fabs(midline.x);
//	data->contactCount = 1;
//	if (xOverlap > 0)
//	{
//		data->contactCount = 1;
//		float yOverlap = (a->halfSize.y/2.0f) + (b->halfSize.y/2.0f) - fabs(midline.y);
//
//		if (yOverlap > 0)
//		{
//			if (xOverlap < yOverlap)
//			{
//				Vector2 normal = midline.x < 0 ? Vector2(1, 0) : Vector2(-1, 0);
//				data->A = a;
//				data->B = b;
//				data->normal = normal;
//				data->penetration = xOverlap;
//				data->restitution = CalculateRestitution(a, b);
//				AABB * shapeA = a->GetOwner()->has(AABB);
//				data->contact[0] = data->normal * shapeA->halfSize.x + transA->GetPositionXY();
//				return;
//			}
//			else
//			{
//				Vector2 normal = midline.y < 0 ? Vector2(0, 1) : Vector2(0, -1);
//				data->A = a;
//				data->B = b;
//				data->normal = normal;
//				data->penetration = yOverlap;
//				data->restitution = CalculateRestitution(a, b);
//				AABB * shapeB = b->GetOwner()->has(AABB)
//				data->contact[0] = data->normal * shapeB->halfSize.y + transB->GetPositionXY();
//				return;
//			}
//		}
//	}
//	// No Collision
//	data->contactCount = 0;
//
//}
//
//void AABBAndCircle(Primitive *shapeAABB, Primitive *shapeCircle, Manifold *data)
//{
//	/*AABB *aabb;
//	Circle *circle;
//	// Create pointers based on what is what
//	if (a->GetID() == Primitive::pCircle)
//	{
//		aabb = reinterpret_cast<AABB *>(b->bodyShape);
//		circle = reinterpret_cast<Circle *>(a->bodyShape);
//	}
//	else
//	{
//		aabb = reinterpret_cast<AABB *>(a->bodyShape);
//		circle = reinterpret_cast<Circle *>(b->bodyShape);
//	}*/
//	Transform* transAABB = shapeAABB->GetOwner()->has(Transform);
//	Transform* transCircle = shapeCircle->GetOwner()->has(Transform);
//
//	//  Calculate the vector between the objects
//	Vector2 midline = transCircle->GetPositionXY() - transAABB->GetPositionXY();
//	//printf("CirclePos: %f, %f", transCircle->GetPositionXY().x, transCircle->GetPositionXY().y);
//	// Closest point on A to the center of B
//	Vector2 closest = midline;
//
//	// Calculate half extent for each axis
//	float x_extent = shapeAABB->halfSize.x /2.0f;
//	float y_extent = shapeAABB->halfSize.y /2.0f;
//
//	// Clamp t0=o point to edges of AABB
//	closest.x = Clamp(-x_extent, x_extent, closest.x);
//	closest.y = Clamp(-y_extent, y_extent, closest.y);
//
//	bool inside = false;
//
//	// If circle is inside, clamp the circle's center to the closest
//	// AABB's edge
//
//	if (midline == closest)
//	{
//		inside = true;
//
//		// Find the closest AABB's axis
//		if (abs(midline.x) > abs(midline.y))
//		{
//			// Clamp to the closest extent
//			if (closest.x > 0)
//				closest.x = x_extent;
//			else
//				closest.x = -x_extent;
//		}
//		// y axis is shorter
//		else
//		{
//			// Clamp to closest extent
//			if (closest.y > 0)
//				closest.y = y_extent;
//			else
//				closest.y = -y_extent;
//		}
//	}
//
//	Vector2 normal = midline - closest;
//	float distance = normal.Magnitude();
//	float radius = shapeCircle->radius;
//
//	// Circle not inside the AABB
//	if (distance > radius * radius && !inside)
//	{
//		data->contactCount = 0;
//		return;
//	}
//
//	distance = sqrtf(distance);
//
//	// If circle is inside AABB,
//	// Collision normal flipped to point outside
//	if (inside)
//	{
//		data->normal = -midline;
//		data->penetration = radius - distance /2.0f;
//		data->restitution = CalculateRestitution(shapeAABB , shapeCircle);
//	}
//	else
//	{
//		data->normal = midline;
//		data->penetration = radius - distance /2.0f;
//		data->restitution = CalculateRestitution(shapeAABB, shapeCircle);
//	}
//
//	// Update contact
//	data->contactCount = 1;
//	data->A = shapeAABB;
//	data->B = shapeCircle;
//}
//
//void CircleAndAABB(Primitive *b, Primitive *a, Manifold *data)
//{
//	AABBAndCircle(a, b, data);
//}
//
//float Clamp(float min, float max, float x)
//{
//	if (x < min)
//		return min;
//	else if (x > max)
//		return max;
//	return x;
//}
