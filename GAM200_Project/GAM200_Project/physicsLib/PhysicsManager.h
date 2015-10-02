//#include "collision_narrow.h"
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#pragma once
#include "Body.h"
#include "Resolution.h"
#include "Collision.h"
#include "../Engine.h"
//#include "Precompiled.h"
// Physics system
class PhysicsManager : public ISystem
{
public:

	PhysicsManager();
	~PhysicsManager();

	std::vector<RigidBody *>bodies; // Holds the bodies
	std::vector<Manifold> contacts; // Holds the contacts
	std::vector<Primitive *>colliders; // Holds the colliders

	// Overloaded methods
	  void Initialize();// override;
    void Update(float dt);//override;
		void Shutdown();// override;

	void IntegrateForces(RigidBody *body, float dt);
	void IntegrateVelocity(RigidBody *body, float dt);
	void Step(float dt);
	void ColliderCheck();
	void RigidBodyCheck();

	//I changed this from a Vector2D so I could load it from Setting
	float GRAVITY = -1.0;
};

extern PhysicsManager *physics;

#endif