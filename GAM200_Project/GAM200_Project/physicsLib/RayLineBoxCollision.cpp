#include "Collision.h"
//#include "Precompiled.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "RayLineBoxCollision.h"


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