
#include "Resolution.h"
#include "Body.h"
//#include <algorithm>
//#include <math.h>
//#include "math_utility.h"
//#include "Precompiled.h"
//#include "Collision.h"
#include "PhysicsManager.h"

//PhysicsMaterial::PhysicsMaterial()
//{
//	staticFriction = 0.5f;
//	staticFriction2 = 0.5f;
//	dynamicFriction = 0.3f;
//	dynamicFriction2 = 0.3f;
//	frictionCombine = 0.0f;
//	//friction = 0.2f;
//}
//
//void Manifold::Solve(void)
//{
//	// Give the current data
//	
//	CollisionRegistry[A->GetID()][B->GetID()](A, B, this);
//}
//
//void Manifold::PreStep(float dt)
//{
//
//	const float EPSILON = 0.0001f;
//
//	// Calculate the average restitution
//	if (A->body && B->body)
//		e = std::min(A->body->restitution, B->body->restitution);
//
//	// Calculate the static and dynamic friction
//	
//	//staticFriction = std::sqrt( A->stFric * B->stFric );
//	//dynamicFriction = std::sqrt( A->dynFric * B->dynFric );
//
//	staticFriction = std::sqrt(A->material.staticFriction *
//		B->material.staticFriction);
//	//printf("%f", staticFriction);
//
//	dynamicFriction = std::sqrt(A->material.dynamicFriction *
//		B->material.dynamicFriction);
//
//	for (unsigned int i = 0; i < contactCount; ++i)
//	{
//		// Calculate the radii
//		Vector2 radii_A = contact[i] - A->pTrans->GetPositionXY();
//		Vector2 radii_B = contact[i] - B->pTrans->GetPositionXY();
//		if (A->body && B->body)
//		{
//			Vector2 relativeVel = B->body->getVelocity() + Vector2::CrossProduct(B->body->angularVelocity, radii_B) -
//				A->body->getVelocity() - Vector2::CrossProduct(A->body->angularVelocity, radii_A);
//
//			if (relativeVel.Magnitude() < ((1.0f / 60.0f) * (Vec2D(0, physics->GRAVITY))).Magnitude() + EPSILON)
//				e = 0.0f;
//		}
//	}
//
//
//}

BodyContact * ContactSet::GetNextContact()
{
	
	return &contactArray[NumberOfContacts++];
}

void ContactSet::Reset()
{
	NumberOfContacts = 0;
}

float BodyContact::CalculateSeparatingVelocity()
{
	Vec2D relativeVelocity = Bodies[0]->Velocity - Bodies[1]->Velocity;

	//Get the separating velocity by projecting along the contact normal
	SeperatingVelocity = Vec2D::DotProduct(relativeVelocity, ContactNormal);

	return SeperatingVelocity;
}

void ResloveContactVelocity(BodyContact& c, float dt)
{
	//Find the velocity of the two object along the contact normal
	float separatingVelocity = c.CalculateSeparatingVelocity();

	if (separatingVelocity > 0)
	{
		//The objects are no longer moving towards each other
		//or the contact they are stationary
		c.ContactImpulse = 0;
		return;
	}

	//This velocity of this collision has to be resolved.

	//To model inelastic collision the kinetic energy of the bodies 
	//needs to be reduced.
	//This technique uses the combined restitution to determine what percentage
	//of the energy along the collision normal is conserved
	float newSepVelocity = -separatingVelocity * c.Restitution;

	const bool AccelerationBuildUp = true;
	//When an object is resting on the ground it is constantly falling
	//due to gravity. This acceleration need be removed or objects will
	//jitter on the ground.

	if (AccelerationBuildUp)
	{
		// Check the velocity build-up due to acceleration only
		Vec2D accCausedVelocity = c.Bodies[0]->Acceleration - c.Bodies[1]->Acceleration;
		float accCausedSepVelocity = Vec2D::DotProduct(accCausedVelocity, c.ContactNormal) * dt;

		// If we've got a closing velocity due to acceleration build-up,
		// remove it from the new separating velocity
		if (accCausedSepVelocity < 0)
		{
			newSepVelocity += c.Restitution * accCausedSepVelocity;

			// Make sure we haven't removed more than was
			// there to remove.
			if (newSepVelocity < 0) newSepVelocity = 0;
		}
	}

	//What is the total change in velocity for the contact?
	float deltaVelocity = newSepVelocity - separatingVelocity;

	//The delta velocity is applied to each object proportional to inverse
	//mass. So the more massive an object is the less of the change
	//in velocity it will receive.
	float totalInverseMass = c.Bodies[0]->InvMass + c.Bodies[1]->InvMass;

	// Calculate the impulse to apply
	float impulse = deltaVelocity / totalInverseMass;

	c.ContactImpulse = impulse;

	// Find the amount of impulse per unit of inverse mass
	Vec2D impulsePerIMass = c.ContactNormal * impulse;

	// Apply impulses: they are applied in the direction of the contact,
	// and in proportion to inverse mass.
	c.Bodies[0]->Velocity = c.Bodies[0]->Velocity + impulsePerIMass * c.Bodies[0]->InvMass;
	// The other body goes in the opposite direction
	c.Bodies[1]->Velocity = c.Bodies[1]->Velocity + impulsePerIMass * -c.Bodies[1]->InvMass;
}

void ResolvePenetration(BodyContact& c, float dt)
{
	// The movement of each object is based on their inverse mass, so
	// total that.
	float totalInverseMass = c.Bodies[0]->InvMass + c.Bodies[1]->InvMass;

	// Find the amount of penetration resolution per unit of inverse mass
	Vec2D movePerIMass = c.ContactNormal * (c.Penetration / totalInverseMass);

	//If stack stability can be increased by not resolving all the penetrations
	//in one step
	movePerIMass *= PHYSICS->PenetrationResolvePercentage;

	// Calculate the the movement amounts
	c.Movement[0] = movePerIMass * c.Bodies[0]->InvMass;
	c.Movement[1] = movePerIMass * -c.Bodies[1]->InvMass;
	//Transform* ownerTrans = GetOwner()->has(Transform);
	// Apply the penetration resolution
	c.Bodies[0]->Position = c.Bodies[0]->Position + c.Movement[0];
	c.Bodies[1]->Position = c.Bodies[1]->Position + c.Movement[1];
}


//Resolve Positions
void ContactSet::ResolvePositions(float dt)
{
	//Resolving penetrations is a tricky problem with large stacks. The only real way to get 
	//good results is by considering all contacts at once at solving them together. This method basically 
	//just keeps poking the bodies until the penetrations are below the penetration slop epsilon. 
	//Better solutions involve building contact graphs, shock propagation and constraint based
	//solvers.
	unsigned iterationsRun = 0;
	unsigned maxIterations = NumberOfContacts * 5;
	const float positionEpsilon = PHYSICS->PenetrationEpsilon;

	while (iterationsRun < maxIterations)
	{
		// Find biggest penetration greater than
		//the correction epsilon
		float maxPenetration = positionEpsilon;
		unsigned contactIndex = NumberOfContacts;
		for (unsigned i = 0; i<NumberOfContacts; i++)
		{
			if (contactArray[i].Penetration > maxPenetration)
			{
				maxPenetration = contactArray[i].Penetration;
				contactIndex = i;
			}
		}
		if (contactIndex == NumberOfContacts) break;

		//Resolve the penetration
		ResolvePenetration(contactArray[contactIndex], dt);

		// Update the penetrations for all related contacts
		Vec2D * movement = contactArray[contactIndex].Movement;
		for (unsigned i = 0; i < NumberOfContacts; i++)
		{
			if (contactArray[i].Bodies[0] == contactArray[contactIndex].Bodies[0])
				contactArray[i].Penetration -= Vec2D::DotProduct(movement[0], contactArray[i].ContactNormal);
			else if (contactArray[i].Bodies[0] == contactArray[contactIndex].Bodies[1])
				contactArray[i].Penetration -= Vec2D::DotProduct(movement[1], contactArray[i].ContactNormal);
			if (contactArray[i].Bodies[1])
			{
				if (contactArray[i].Bodies[1] == contactArray[contactIndex].Bodies[0])
					contactArray[i].Penetration += Vec2D::DotProduct(movement[0], contactArray[i].ContactNormal);
				else if (contactArray[i].Bodies[1] == contactArray[contactIndex].Bodies[1])
					contactArray[i].Penetration += Vec2D::DotProduct(movement[1], contactArray[i].ContactNormal);
			}
		}
		++iterationsRun;
	}
}

//Resolve Velocities of all contacts
void ContactSet::ResolveVelocities(float dt)
{
	unsigned iterationsRun = 0;
	unsigned maxIterations = NumberOfContacts * 5;
	while (iterationsRun < maxIterations)
	{
		// Find the contact with the largest closing velocity;
		float maxVelocity = FLT_MAX;
		unsigned contactIndex = NumberOfContacts;
		for (unsigned i = 0; i < NumberOfContacts; i++)
		{
			float sepVel = contactArray[i].CalculateSeparatingVelocity();
			if (sepVel < 0 && sepVel < maxVelocity)
			{
				maxVelocity = sepVel;
				contactIndex = i;
			}
		}

		// Do we have anything worth resolving?
		if (contactIndex == NumberOfContacts) break;

		// Resolve this contact velocity
		ResloveContactVelocity(contactArray[contactIndex], dt);

		++iterationsRun;
	}
}

void ContactSet::ResolveContacts(float dt)
{
	this->ResolvePositions(dt);
	this->ResolveVelocities(dt);
}






//void Manifold::AppyImpulse(void)
//{
	// If static
	//RigidBody* 
	//if (A->body->isStatic && B->body->isStatic)
	//{
	//	A->body->getVelocity().Clear();
	//	B->body->getVelocity().Clear();

	//	return;
	//}

	//if (A->body->isGhost == true || B->body->isGhost == true)
	//{
	//	return;
	//}

	//for (unsigned int i = 0; i < contactCount; ++i)
	//{
	//	// Calculate radii from center of mass to contact
	//	Vector2 radii_a = contact[i] - A->body->pTrans->GetPositionXY();
	//	Vector2 radii_b = contact[i] - B->body->pTrans->GetPositionXY();

	//	// Relative velocity at contact
	//	Vector2 relativeVel = B->body->getVelocity() + Vec2D::CrossProduct(B->body->angularVelocity, radii_b) -
	//		A->body->getVelocity() - Vec2D::CrossProduct(A->body->angularVelocity, radii_a);

	//	// Relative velocity along normal
	//	float contactVel = Vec2D::DotProduct(relativeVel, normal);

	//	// If velocities are separating do not resolve
	//	if (contactVel > 0)
	//	{
	//		return;
	//	}

	//	float crossA = Vec2D::CrossProduct(radii_a, normal);
	//	float crossB = Vec2D::CrossProduct(radii_b, normal);
	//	float invMassSum = A->body->invMass + B->body->invMass + (crossA * crossA) * A->body->invInertia + (crossB * crossB) * B->body->invInertia;
	//	e = 0.2003f; //epsilon value
	//	// Calculate the impulse scalar
	//	float j = -(1.0f + e) * contactVel;
	//	j /= invMassSum;
	//	j /= (float)contactCount;

	//	// Apply the impulse
	//	Vector2 impulse = normal * (j /2);
	//	A->body->ApplyImpulse(-impulse, radii_a);
	//	B->body->ApplyImpulse(impulse, radii_b);

	//	// Friction impulse
	//	relativeVel = B->body->getVelocity() + Vec2D::CrossProduct(B->body->angularVelocity, radii_b) -
	//		A->body->getVelocity() - Vec2D::CrossProduct(A->body->angularVelocity, radii_a);

	//	Vector2 tangentVec = relativeVel - (normal * Vec2D::DotProduct(relativeVel, normal));
	//	tangentVec.Normalize();

	//	// Solve magnitude to apply along friction vector
	//	float jt = -Vector2::DotProduct(relativeVel, tangentVec);
	//	jt /= invMassSum;
	//	jt /= (float)contactCount;

	//	// Not applying tiny friction impulses
	//	if (jt == 0.0f)
	//	{
	//		return;
	//	}

	//	// Clamp magnitude of friction and create impulse vector
	//	Vector2 tangentImpulse;
	//	tangentImpulse = tangentVec * jt;
	//	if (std::abs(jt) < j * staticFriction)
	//		tangentImpulse = tangentVec *jt;
	//	else
	//		tangentImpulse = tangentVec * -j * dynamicFriction;


	//
	//}


//}

//void Manifold::CorrectPosition(void)
//{
	////HOLY FUCK THIS MESSED UP LIKE &%@!# :*(, NEVER SET isStatic to true, did I even do that? fk
	//if (A->body->isGhost == true || B->body->isGhost == true )
	//{
	//	return;
	//}
	////???
	////if (A->body->isStatic == true)
	////{
	////	return;
	////}

	////if (A->body->isStatic == false)
	////{
	////	return;
	////}

	//const float slop = 0.01f;//0.01
	//const float percent = 0.4f;//0.4f; // 40% //0.2

	//// Allows object to penetrate slightly without position correction from occurring 
	// //change std max to mim so we can pull things! max for push things
	//Vector2 correction = (std::min(penetration - slop, 0.0f) / (A->body->invMass + B->body->invMass)) * normal * percent;


	//	Vector2 Apos = A->body->pTrans->GetPositionXY();
	//	Vector2 Bpos = B->body->pTrans->GetPositionXY();
	//	if (A->body->isStatic == false)
	//	{
	//		A->body->pTrans->SetPosition(Apos - correction * A->body->invMass);
	//		//A->body->setVelocity(0.0f, 0.0f);
	//	}
	//	//Apos -= correction * A->body->invMass;
	//	//Bpos += correction * A->body->invMass;
	//	if (B->body->isStatic == false)
	//	{
	//		B->body->pTrans->SetPosition(Bpos + correction * B->body->invMass);
	//		//B->body->setVelocity(0.0f, 0.0f);
	//	}
	//	//if (A->body->pTrans->GetPositionXY().x == B->body->pTrans->GetPositionXY().x)
	//	//{
	//	//	Vector2 correction = Vec2D(0.0f,0.0f);
	//	//}
	//	//
	//	//Vector2 no = Vec2D();
	//	//if (A->body != NULL && B->body != NULL);
	//	//{
	//	///*	A->body->pTrans->GetPositionXY(Apos,Bpos);
	//	//	B->body->pTrans->SetPosition.y;*/
	//	//	A->body->pTrans->SetPosition(Apos);
	//	//	B->body->pTrans->SetPosition(Bpos);
	//	//}
	//	
	//	//if (A->body != nullptr)
	//		//A->body->pTrans->SetPosition(Apos, Bpos);
	//	//printf("correction: %i", correction);
	//	printf("BposInRes: %f, %f", B->body->pTrans->pos2d);
	//	printf("invMass: %f", A->body->invMass);
	//	printf("invMass: %f", B->body->invMass);
	//	//printf("normal: %f", normal);
	//	//printf("slop: %f", slop);
	//	printf("penetration: %f", penetration);
	//	printf("Bvelocity %f", B->body->getVelocity().y);
	//	printf("Avelocity %f", A->body->getVelocity().y);
//}
