/*****************************************************************************/
/*!
\file    Resolution.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file for solving the contacts/collision.
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
#ifndef RESOLUTION_H
#define RESOLUTION_H
//#pragma once
//#include "Body.h"
#include "Collision.h"
//#include "primitive.h"
#include "math_utility.h"


//
struct PhysicsMaterial
{
	float staticFriction;
	float staticFriction2;
	float dynamicFriction;
	float dynamicFriction2;
	float frictionCombine;

	PhysicsMaterial();
};
// Contact Generation or Manifold
struct Manifold
{
	Manifold() {}

	//Manifold(RigidBody *a, RigidBody *b) : A(a), B(b) {}
	Manifold(Body *a, Body *b) : A(a), B(b) {}
	//RigidBody *A;
	Body *A;
		//RigidBody *B;
	Body *B;
	float penetration;
	//Vector2 position;

	float restitution;

	// Combined frictions
	float friction;

	Vector2 normal;

	Vector2 contact[2];

	float staticFriction;

	float dynamicFriction;

	float e; // epsilon


	unsigned contactCount; // The number of contacts found so far

	void Solve(void);
	void PreStep(float dt);
	void AppyImpulse(void);
	void CorrectPosition(void);


};


class contactList
{
public:
	ManifoldSet * GetNewContact();
	void ResolveContacts(float dt);
	void Reset();
	Shape * myshape;


private:
	friend class Physics;
	static const int MaxContacts = 1024;
	ManifoldSet contactSet[MaxContacts];
	unsigned TotalContacts;
	void CorrectVelocity(float dt);
	void CorrectPosition(float dt);
};
#endif 