//#include "collision_narrow.h"
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#pragma once
#include "Body.h"
#include "Resolution.h"
#include "Collision.h"
#include "../Engine.h"
#include "../ComponentCreator.h"

#include "ObjectLinkedList.h"

//#include "Precompiled.h"
// Physics system
//class PhysicsManager : public ISystem
//{
//public:
//
//	PhysicsManager();
//	~PhysicsManager();
//
//	std::vector<RigidBody *>bodies; // Holds the bodies
//	std::vector<Manifold> contacts; // Holds the contacts
//	std::vector<Primitive *>colliders; // Holds the colliders
//
//	// Overloaded methods
//	  void Initialize();// override;
//    void Update(float dt);//override;
//		void Shutdown();// override;
//
//	void IntegrateForces(RigidBody *body, float dt);
//	void IntegrateVelocity(RigidBody *body, float dt);
//	void Step(float dt);
//	void ColliderCheck();
//	void RigidBodyCheck();
//
//	//I changed this from a Vector2D so I could load it from Setting
//	float GRAVITY = -.5f;
//
//
//	// from sample engine
//	bool AdvanceStep;
//	bool StepModeActive;
//
//	//typedef ObjectLinkList<Body>::iterator BodyIterator;
//	//ObjectLinkList<Body> Bodies;
//
//	//Gravity of the world
//	Vec2D Gravity;
//	//Max velocity for a physics body
//	float MaxVelocity;
//	float MaxVelocitySq;
//
//	//See Resolution.cpp for use
//	//Position correction tolerance
//	float PenetrationEpsilon;
//	//Position correction resolve percentage
//	float PenetrationResolvePercentage;
//
//private:
//	float TimeAccumulation;
//	//CollsionDatabase Collsion;
//	ContactSet Contacts;
//
//};
//
//extern PhysicsManager *physics;


///Message sent when there is a Collsion between two
///Body Components.
class MessageCollide : public Message
{
public:
	MessageCollide() : Message(Mid::Collide) {};
	Vec2D ContactNormal;
	float Impulse;
	GOC * CollidedWith;
};

///	Basic 2D iterative impulse physics engine system.
/// Provides the Body Component.
class Physics : public ISystem
{
public:
	Physics();
	virtual void Update(float dt);
	virtual std::string GetName(){ return "Physics"; }
	void SendMessage(Message * m);
	GOC * TestPoint(Vec2D testPosition);
	void Initialize();
private:
	void IntegrateBodies(float dt);
	void DetectContacts(float dt);
	void PublishResults();
	void DebugDraw();
	void Step(float dt);
	bool DebugDrawingActive;
	float TimeAccumulation;
	CollsionDatabase Collsion;
	ContactSet Contacts;

public:
	bool AdvanceStep;
	bool StepModeActive;

	typedef ObjectLinkList<Body>::iterator BodyIterator;
	ObjectLinkList<Body> Bodies;

	//Gravity of the world
	Vec2D Gravity;
	//Max velocity for a physics body
	float MaxVelocity;
	float MaxVelocitySq;

	//See Resolution.cpp for use
	//Position correction tolerance
	float PenetrationEpsilon;
	//Position correction resolve percentage
	float PenetrationResolvePercentage;

};

//A global pointer to the Physics system, used to access it globally.
extern Physics* PHYSICS;


#endif