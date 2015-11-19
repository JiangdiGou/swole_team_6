/*****************************************************************************/
/*!
\file    PhysicsManager.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file for physics engine implementation
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#pragma once
#include "Body.h"
#include "Resolution.h"
#include "Collision.h"
#include "../Engine.h"
#include "../ComponentCreator.h"
#include "ObjectLinkedList.h"



///Message sent when there is a Collsion between two
///Body Components.
const static unsigned int MaxContacts = 1024;

class MessageCollide : public Message
{
public:
	MessageCollide() : Message(Mid::Collide) {};
	Vec2D ContactNormal;
	float Impulse;
	GOC * CollidedWith;
};
class Collision : public Message
{
public:
  Collision() : Message(Mid::Collision), otherObj(NULL) {};
  Collision(ShapeAAB* otherObj) : Message(Mid::Collision), otherObj(otherObj) {};
  ShapeAAB* otherObj;
};

/// Provides the Body Component.
class Physics : public ISystem
{
public:
	Physics();
	virtual void Update(float dt);
	virtual std::string GetName(){ return "Physics"; }
	void SendMessage(Message * m);
	void Initialize();
private:
	void IntegrateBodies(float dt);
	void DetectContacts(float dt);
	void solveMessage();
	void DebugDraw();
	void Step(float dt);
	bool DebugDrawingActive;
	float TimeAccumulation;
	CollsionDatabase Collsion;
  Collision AllCollisions[MaxContacts];
  int nextCollisionIndex = 0;
	contactList Contacts;

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