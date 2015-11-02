
#include "Resolution.h"
#include "Body.h"
//#include <algorithm>
//#include <math.h>
//#include "math_utility.h"
//#include "Precompiled.h"
//#include "Collision.h"
#include "PhysicsManager.h"


ManifoldSet * contactList::GetNewContact()
{
	
	return &contactSet[TotalContacts++];
}

void contactList::Reset()
{
	TotalContacts = 0;
}

float ManifoldSet::GetSeparateVelocity()
{
	
	Vec2D relativeVelocity = Bodies[0]->Velocity - Bodies[1]->Velocity;

	//Get the separating velocity by projecting along the contact normal
	SeperatingVelocity = Vec2D::DotProduct(relativeVelocity, ContactNormal);

	return SeperatingVelocity;
}

void SolveVelocity(ManifoldSet& c, float dt)
{
	
	//Find the velocity of the two object along the contact normal
	float separatingVelocity = c.GetSeparateVelocity();

	if (separatingVelocity > 0)
	{
		//The objects are no longer moving towards each other
		//or the contact they are stationary
		c.ContactImpulse = 0;
		return;
	}

	//This velocity of this collision has to be resolved.
	float newSepVelocity = -separatingVelocity * c.Restitution;

	const bool accelerationFlag = true;
	//When an object is resting on the ground it is constantly falling
	//due to gravity. This acceleration need be removed 

	if (accelerationFlag)
	{
		// Check the velocity build-up due to acceleration only
		Vec2D VelocityViaAcceleration = c.Bodies[0]->Acceleration - c.Bodies[1]->Acceleration;
		float NewVelocity = Vec2D::DotProduct(VelocityViaAcceleration, c.ContactNormal) * dt;

		// If we've got a closing velocity due to acceleration build-up,
		// remove it from the new separating velocity
		if (NewVelocity < 0)
		{
			newSepVelocity += c.Restitution * NewVelocity;

			// Make sure we haven't removed more than was
			// there to remove.
			if (newSepVelocity < 0) newSepVelocity = 0;
		}
	}

	//What is the total change in velocity for the contact?
	float deltaVelocity = newSepVelocity - separatingVelocity;

	//The delta velocity is applied to each object proportional to inverse
	//mass. 
	float totalInverseMass = c.Bodies[0]->InvMass + c.Bodies[1]->InvMass;

	// Calculate the impulse to apply
	float impulse = deltaVelocity / totalInverseMass;

	c.ContactImpulse = impulse;

	// Find the amount of impulse per unit of inverse mass
	Vec2D impulsePerIMass = c.ContactNormal * impulse;

	c.Bodies[0]->Velocity = c.Bodies[0]->Velocity + impulsePerIMass * c.Bodies[0]->InvMass;
	// The other body goes in the opposite direction
	c.Bodies[1]->Velocity = c.Bodies[1]->Velocity + impulsePerIMass * -c.Bodies[1]->InvMass;
}

void SolvePenetration(ManifoldSet& c, float dt)
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

	// Apply the penetration resolution
	c.Bodies[0]->Position = c.Bodies[0]->Position +c.Movement[0];
	c.Bodies[1]->Position = c.Bodies[1]->Position +c.Movement[1];
}


void contactList::CorrectPosition(float dt)
{
	unsigned k = 0;
	unsigned maxIterations = TotalContacts * 5;
	const float positionEpsilon = PHYSICS->PenetrationEpsilon;

	while (k < maxIterations)
	{
		// Find biggest penetration 
		float maxPenetration = positionEpsilon;
		unsigned contactIndex = TotalContacts;
		for (unsigned i = 0; i < TotalContacts; i++)
		{
			if (contactSet[i].Penetration > maxPenetration)
			{
				maxPenetration = contactSet[i].Penetration;
				contactIndex = i;
			}
		}
		if (contactIndex == TotalContacts) break;

		//solve the penetration
		SolvePenetration(contactSet[contactIndex], dt);

		// Update the penetrations for all related contacts
		Vec2D * movement = contactSet[contactIndex].Movement;
		for (unsigned i = 0; i < TotalContacts; i++)
		{
			if (contactSet[i].Bodies[0] == contactSet[contactIndex].Bodies[0])
				contactSet[i].Penetration -= Vec2D::DotProduct(movement[0], contactSet[i].ContactNormal);
			else if (contactSet[i].Bodies[0] == contactSet[contactIndex].Bodies[1])
				contactSet[i].Penetration -= Vec2D::DotProduct(movement[1], contactSet[i].ContactNormal);
			if (contactSet[i].Bodies[1])
			{
				if (contactSet[i].Bodies[1] == contactSet[contactIndex].Bodies[0])
					contactSet[i].Penetration += Vec2D::DotProduct(movement[0], contactSet[i].ContactNormal);
				else if (contactSet[i].Bodies[1] == contactSet[contactIndex].Bodies[1])
					contactSet[i].Penetration += Vec2D::DotProduct(movement[1], contactSet[i].ContactNormal);
			}
		}
		++k;
	}
}


void contactList::CorrectVelocity(float dt)
{
	unsigned k = 0;
	unsigned maxIterations = TotalContacts * 5;
	while (k < maxIterations)
	{
		// Find the contact with the largest closing velocity;
		float maxVelocity = FLT_MAX;
		unsigned contactIndex = TotalContacts;
		for (unsigned i = 0; i < TotalContacts; i++)
		{
			float sepVel = contactSet[i].GetSeparateVelocity();
			if (sepVel < 0 && sepVel < maxVelocity)
			{
				maxVelocity = sepVel;
				contactIndex = i;
			}
		}

		// Do we have anything worth resolving?
		if (contactIndex == TotalContacts) break;

		// Resolve this contact velocity
		SolveVelocity(contactSet[contactIndex], dt);

		++k;
	}
}

void contactList::ResolveContacts(float dt)
{
	//if (myshape->body->IsGhost == true)
	//{	
	//	return;
	//} 

	this->CorrectPosition(dt);
	this->CorrectVelocity(dt);
}

