/*****************************************************************************/
/*!
\file    Collision.h
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the header file of the 
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
#ifndef COLLISION_H
#define COLLISION_H
//#include "primitive.h"
//#include "Resolution.h"
//#include "Body.h"
#include "math_utility.h"
#include "../Composition.h"

//sample
class Body;

///Data for a contact between two bodies.
///Used to resolve world collisions.
struct ManifoldSet
{
	
	
	Body* Bodies[2];
	Vec2D Movement[2];
	Vec2D ContactNormal;
	float Penetration;
	float Restitution;
	float FrictionCof;

	float SeperatingVelocity;
	float ContactImpulse;
	float GetSeparateVelocity();
};

///Base Shape class
class Shape : public GameComponent
{
public:
	enum ShapeId
	{
		SidCircle,
		SidBox,
		SidNumberOfShapes,
		SidLine
	};
	ShapeId Id;
	Body * body;
	Shape(ShapeId pid) : Id(pid) {};
  //void Initialize() override;
	//virtual void Draw() = 0;
	//virtual bool TestPoint(Vec2D) = 0;
	//virtual BoundingCircle GetBoundingCircle() const = 0;
	//virtual std::pair<bool, float> Intersect(Ray const& ray) const = 0;
	//virtual void Print() const = 0;
	//virtual ~Shape();
};

//Line shape??
class ShapeLine : public Shape
{
	public:
		ShapeLine() : Shape(SidLine){};
    void SerializeRead(Serializer& str) override;
    void SerializeWrite(Serializer& str) override;
		Vec2D base;
		Vec2D direction;
		
};


///Circle shape.
class ShapeCircle : public Shape
{
public:
	ShapeCircle() : Shape(SidCircle){};
	float Radius;
	virtual void Draw();
	virtual bool TestPoint(Vec2D);
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;
};

///Axis Aligned Box Shape
class ShapeAAB : public Shape
{
public:
	ShapeAAB() : Shape(SidBox){};
  void Initialize() override;
  void Update(float dt) override;
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;
  void SendMessages(Message* m) override;
	Vec2D Extents;
	Vec2D origin = Vec2D(0.0f,0.0f);
	virtual void Draw();
	virtual bool TestPoint(Vec2D);
  std::vector<ShapeAAB*> PrevCollidingObjects;
  std::vector<ShapeAAB*> CurCollidingObjects;
};
class CollisionStarted : public Message
{
public:
  CollisionStarted(ShapeAAB* otherObj) : Message(Mid::CollisionStarted), otherObj(otherObj) {};
  ShapeAAB* otherObj;
};

class CollisionPersisted : public Message
{
public:
  CollisionPersisted(ShapeAAB* otherObj) : Message(Mid::CollisionPersisted), otherObj(otherObj) {};
  ShapeAAB* otherObj;
};

class CollisionEnded : public Message
{
public:
  CollisionEnded(ShapeAAB* otherObj) : Message(Mid::CollisionEnded), otherObj(otherObj) {};
  ShapeAAB* otherObj;
};

class contactList;
typedef bool(*CollisionTest)(Shape*a, Vec2D at, Shape*b, Vec2D bt, contactList*c);

///The collision database provides collision detection between shape types.
class CollsionDatabase
{
public:
	CollsionDatabase();
	CollisionTest CollsionRegistry[Shape::SidNumberOfShapes][Shape::SidNumberOfShapes];
	bool GenerateContacts(Shape* shapeA, Vec2D poistionA, Shape* shapeB, Vec2D poistionB, contactList*c);
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
//struct ManifoldSet
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
//	float GetSeparateVelocity();
//};

#endif