#ifndef COLLISION_H
#define COLLISION_H
//#include "primitive.h"
//#include "Resolution.h"
//#include "Body.h"
//#include "CollisionCheck.h"
#include "math_utility.h"
#include "../Composition.h"

//sample
class Body;

///Data for a contact between two bodies.
///Used to resolve world collisions.
struct BodyContact : public GameComponent
{
	Body* Bodies[2];
	Vec2D Movement[2];
	Vec2D ContactNormal;
	float Penetration;
	float Restitution;
	float FrictionCof;

	float SeperatingVelocity;
	float ContactImpulse;
	float CalculateSeparatingVelocity();
};

///Base Shape class
class Shape : public GameComponent
{
public:
	enum ShapeId
	{
		SidCircle,
		SidBox,
		SidNumberOfShapes
	};
	ShapeId Id;
	Body * body;
	Shape(ShapeId pid) : Id(pid) {};
	virtual void Draw() = 0;
	virtual bool TestPoint(Vec2D) = 0;
};

///Circle shape.
class ShapeCircle : public Shape
{
public:
	ShapeCircle() : Shape(SidCircle){};
	float Radius;
	virtual void Draw();
	virtual bool TestPoint(Vec2D);
};

///Axis Aligned Box Shape
class ShapeAAB : public Shape
{
public:
	ShapeAAB() : Shape(SidBox){};
	Vec2D Extents;
	virtual void Draw();
	virtual bool TestPoint(Vec2D);
};

class ContactSet;
typedef bool(*CollisionTest)(Shape*a, Vec2D at, Shape*b, Vec2D bt, ContactSet*c);

///The collision database provides collision detection between shape types.
class CollsionDatabase
{
public:
	CollsionDatabase();
	CollisionTest CollsionRegistry[Shape::SidNumberOfShapes][Shape::SidNumberOfShapes];
	bool GenerateContacts(Shape* shapeA, Vec2D poistionA, Shape* shapeB, Vec2D poistionB, ContactSet*c);
	void RegisterCollsionTest(Shape::ShapeId a, Shape::ShapeId b, CollisionTest test);
};

float Clamp(float, float, float);
//struct Manifold;
//class RigidBody;
//
//typedef void(*CollisionTest)(Primitive *a, Primitive *b, Manifold *data);
//extern CollisionTest CollisionRegistry[Primitive::pCount][Primitive::pCount];
//
//void CircleAndCircle(Primitive *a, Primitive *b, Manifold *data);
//void AABBAndAABB(Primitive *a, Primitive *b, Manifold *data);
//void AABBAndCircle(Primitive *a, Primitive *b, Manifold *data);
//void CircleAndAABB(Primitive *b, Primitive *a, Manifold *data);
//float Clamp(float, float, float);
//
/////Data for a contact between two bodies.
/////Used to resolve world collisions.
//struct BodyContact
//{
//	RigidBody* Bodies[2];
//	Vec2D Movement[2];
//	Vec2D ContactNormal;
//	float Penetration;
//	float Restitution;
//	float FrictionCof;
//
//	float SeperatingVelocity;
//	float ContactImpulse;
//	float CalculateSeparatingVelocity();
//};

#endif