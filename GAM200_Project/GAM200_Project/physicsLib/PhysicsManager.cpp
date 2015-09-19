#include "other stuff"
#include "PhysicsManager.h"
#include "game setting file?"

PhysicsManager *physics = nullptr;


//PhysicsManager::PhysicsManager() : ISystem("Physics", SystemType::ST_Physics)
//{
//	float *temp = NULL;
//	GlobalSettings->GetFloatValue("___ PHYSICS SETTINGS ___", temp, false);
//	GlobalSettings->GetFloatValue("Gravity", GRAVITY, true);
//}

PhysicsManager::~PhysicsManager()
{
}

bool PhysicsManager::Initialize()
{
	return true;
}

void PhysicsManager::Update(float dt)
{
	Step(dt);
}

void PhysicsManager::Shutdown()
{
	colliders.clear();
	bodies.clear();
}


void PhysicsManager::RigidBodyCheck()
{
	// Go through the bodies
	for (unsigned int i = 0; i < bodies.size(); ++i)
	{
		if (bodies[i] == NULL)
		{
			continue;
		}

		RigidBody *a = bodies[i];

		// Loop through the next body
		for (unsigned int j = i + 1; j < bodies.size(); ++j)
		{
			RigidBody *b = bodies[j];

			// Check if these object are static
			if (a->isStatic == true && b->isStatic == true)
			{
				continue;
			}

			// Set manifold data
			Manifold m(a, b);

			// Solve
			m.Solve();

			//Check if there's any contact count
			if (m.contactCount)
			{
				// Append new element to the end
				contacts.emplace_back(m);
			}
		}
	}
}
void PhysicsManager::Step(float dt)
{

	ColliderCheck();

	// Clear any old information in the vector
	contacts.clear();

	RigidBodyCheck();

	// Integrate forces
	for (unsigned int i = 0; i < bodies.size(); ++i)
	{
		IntegrateForces(bodies[i], dt);
	}

	// Pre-Steps
	for (unsigned int i = 0; i < contacts.size(); ++i)
	{
		contacts[i].PreStep(dt);
	}

	//Solve collisions
	for (int j = 0; j < 10/*TEMP NUMBER*/; ++j)
	{
		for (unsigned int i = 0; i < contacts.size(); ++i)
		{
			contacts[i].AppyImpulse();
		}
	}

	// Integrate Velocities
	for (unsigned int i = 0; i < bodies.size(); ++i)
	{
		IntegrateVelocity(bodies[i], dt);
	}

	//Correct Positions
	for (unsigned int i = 0; i < contacts.size(); ++i)
	{
		contacts[i].CorrectPosition();
	}

	// Clear forces
	for (unsigned int i = 0; i < bodies.size(); ++i)
	{
		RigidBody *b = bodies[i];
		b->forceAccum.Clear();
	}

	for (unsigned int i = 0; i < bodies.size(); ++i)
	{
		bodies[i]->Update(dt);
	}
}

void PhysicsManager::IntegrateForces(RigidBody *body, float dt)
{
	// Skip if static
	if (body->isStatic == true)
	{
		return;
	}

	if (body->useGravity)
	{
		// Symplectic Euler w/ gravity
		body->velocity += ((body->forceAccum * body->invMass + Vector2D(0, *physics->GRAVITY)) * (dt / 2.0f));
	}
	else
	{
		// Without gravity
		body->velocity += ((body->forceAccum * body->invMass) * (dt / 2.0f));
	}
}

void PhysicsManager::IntegrateVelocity(RigidBody *body, float dt)
{
	// Skip if static
	if (body->isStatic == true)
	{
		return;
	}
	body->position += body->velocity * dt;
	body->orientation += body->angularVelocity * dt;
	body->SetOrientation(body->orientation);
	IntegrateForces(body, dt);
}
