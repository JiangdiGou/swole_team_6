
#include "Resolution.h"
//#include <algorithm>
//#include <math.h>
//#include "math_utility.h"
#include "Precompiled.h"

PhysicsMaterial::PhysicsMaterial()
{
	staticFriction = 0.5f;
	staticFriction2 = 0.5f;
	dynamicFriction = 0.3f;
	dynamicFriction2 = 0.3f;
	frictionCombine = 0.0f;
	//friction = 0.2f;
}

void Manifold::Solve(void)
{
	// Give the current data
	
	CollisionRegistry[A->GetID()][B->GetID()](A, B, this);
}

void Manifold::PreStep(float dt)
{

	const float EPSILON = 0.0001f;

	// Calculate the average restitution
	if (A->body && B->body)
		e = std::min(A->body->restitution, B->body->restitution);

	// Calculate the static and dynamic friction
	
	//staticFriction = std::sqrt( A->stFric * B->stFric );
	//dynamicFriction = std::sqrt( A->dynFric * B->dynFric );

	staticFriction = std::sqrt(A->material.staticFriction *
		B->material.staticFriction);

	dynamicFriction = std::sqrt(A->material.dynamicFriction *
		B->material.dynamicFriction);

	for (unsigned int i = 0; i < contactCount; ++i)
	{
		// Calculate the radii
		Vector2 radii_A = contact[i] - A->pTrans->GetPositionXY();
		Vector2 radii_B = contact[i] - B->pTrans->GetPositionXY();
		if (A->body && B->body)
		{
			Vector2 relativeVel = B->body->getVelocity() + Vector2::CrossProduct(B->body->angularVelocity, radii_B) -
				A->body->getVelocity() - Vector2::CrossProduct(A->body->angularVelocity, radii_A);

			if (relativeVel.Magnitude() < ((1.0f / 60.0f) * (Vec2D(0, physics->GRAVITY))).Magnitude() + EPSILON)
				e = 0.0f;
		}
	}


}

void Manifold::AppyImpulse(void)
{
	// If static
	//RigidBody* 
	if (A->body->isStatic && B->body->isStatic)
	{
		A->body->getVelocity().Clear();
		B->body->getVelocity().Clear();
		return;
	}

	if (A->body->isGhost == true || B->body->isGhost == true)
	{
		return;
	}

	for (unsigned int i = 0; i < contactCount; ++i)
	{
		// Calculate radii from center of mass to contact
		Vector2 radii_a = contact[i] - A->body->pTrans->GetPositionXY();
		Vector2 radii_b = contact[i] - B->body->pTrans->GetPositionXY();

		// Relative velocity at contact
		Vector2 relativeVel = B->body->getVelocity() + Vec2D::CrossProduct(B->body->angularVelocity, radii_b) -
			A->body->getVelocity() - Vec2D::CrossProduct(A->body->angularVelocity, radii_a);

		// Relative velocity along normal
		float contactVel = Vec2D::DotProduct(relativeVel, normal);

		// If velocities are separating do not resolve
		if (contactVel > 0)
		{
			return;
		}

		float crossA = Vec2D::CrossProduct(radii_a, normal);
		float crossB = Vec2D::CrossProduct(radii_b, normal);
		float invMassSum = A->body->invMass + B->body->invMass + (crossA * crossA) * A->body->invInertia + (crossB * crossB) * B->body->invInertia;
		e = 0.2003f; //epsilon value
		// Calculate the impulse scalar
		float j = -(1.0f + e) * contactVel;
		j /= invMassSum;
		j /= (float)contactCount;

		// Apply the impulse
		Vector2 impulse = normal * (j /2);
		A->body->ApplyImpulse(-impulse, radii_a);
		B->body->ApplyImpulse(impulse, radii_b);

		// Friction impulse
		relativeVel = B->body->getVelocity() + Vec2D::CrossProduct(B->body->angularVelocity, radii_b) -
			A->body->getVelocity() - Vec2D::CrossProduct(A->body->angularVelocity, radii_a);

		Vector2 tangentVec = relativeVel - (normal * Vec2D::DotProduct(relativeVel, normal));
		tangentVec.Normalize();

		// Solve magnitude to apply along friction vector
		float jt = -Vector2::DotProduct(relativeVel, tangentVec);
		jt /= invMassSum;
		jt /= (float)contactCount;

		// Not applying tiny friction impulses
		if (jt == 0.0f)
		{
			return;
		}

		// Clamp magnitude of friction and create impulse vector
		Vector2 tangentImpulse;
		tangentImpulse = tangentVec * jt;
		if (std::abs(jt) < j * staticFriction)
			tangentImpulse = tangentVec *jt;
		else
			tangentImpulse = tangentVec * -j * dynamicFriction;


	
	}


}

void Manifold::CorrectPosition(void)
{
	if (A->body->isGhost == true || B->body->isGhost == true)
	{
		return;
	}

	const float slop = 0.05f;//0.01
	const float percent = 0.8f;//0.4f; // 40% //0.2

	// Allows object to penetrate slightly without position correction from occurring 
	 //change std max to mim so we can pull things! max for push things
	Vector2 correction = (std::max(penetration - slop, 0.0f) / (A->body->invMass + B->body->invMass)) * normal * percent /2.0f;

	Vector2 Apos = A->body->pTrans->GetPositionXY();
	Vector2 Bpos = B->body->pTrans->GetPositionXY();
	A->body->pTrans->SetPosition(Apos - correction * A->body->invMass);
	B->body->pTrans->SetPosition(Bpos + correction * B->body->invMass) ;

}
