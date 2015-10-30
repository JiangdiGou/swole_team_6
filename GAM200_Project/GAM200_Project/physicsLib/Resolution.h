#ifndef RESOLUTION_H
#define RESOLUTION_H
//#pragma once
//#include "Body.h"
#include "Collision.h"
//#include "primitive.h"
#include "math_utility.h"

//engine include 



//struct Contact
//{
//	Contact() : Pn(0.0f), Pt(0.0f), Pnb(0.0f), massNormal(0.0f), massTangent(0.0f), bias(0.0f) {}
//	Vector2 position;
//	Vector2 normal;
//	Vector2 r1, r2;
//	float seperation;
//	float Pn; // accumulated normal impulse
//	float Pt; // accumulated tangent impulse
//	float Pnb; // accumulated normal impulse for position bias
//	float  massNormal, massTangent;
//	float bias;
//
//};
//
//struct PhysicsMaterial
//{
//	float staticFriction;
//	float staticFriction2;
//	float dynamicFriction;
//	float dynamicFriction2;
//	float frictionCombine;
//
//	PhysicsMaterial();
//};
//// Contact Generation or Manifold
//struct Manifold
//{
//	Manifold() {}
//
//	//Manifold(RigidBody *a, RigidBody *b) : A(a), B(b) {}
//	Manifold(Primitive *a, Primitive *b) : A(a), B(b) {}
//	//RigidBody *A;
//	Primitive *A;
//		//RigidBody *B;
//	Primitive *B;
//	float penetration;
//	//Vector2 position;
//
//	float restitution;
//
//	// Combined frictions
//	float friction;
//
//	Vector2 normal;
//
//	Vector2 contact[2];
//
//	float staticFriction;
//
//	float dynamicFriction;
//
//	float e; // epsilon
//
//	Contact contacts[2];
//
//	unsigned contactCount; // The number of contacts found so far
//
//	void Solve(void);
//	void PreStep(float dt);
//	void AppyImpulse(void);
//	void CorrectPosition(void);
//
//
//};


class ContactSet
{
public:
	BodyContact * GetNextContact();
	void ResolveContacts(float dt);
	void Reset();
	Shape * myshape;


private:
	friend class Physics;
	static const int MaxContacts = 1024;
	BodyContact contactArray[MaxContacts];
	unsigned NumberOfContacts;
	void ResolveVelocities(float dt);
	void ResolvePositions(float dt);
};
#endif 