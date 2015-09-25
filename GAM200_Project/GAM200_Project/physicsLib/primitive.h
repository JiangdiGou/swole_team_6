#ifndef PRIMITIVE_H
#define PRIMITIVE_H
#include <cstdlib>
#include "Body.h"
#include "Transform.h"
//#include "Precompiled.h"
#include "../Composition.h"
#include "Resolution.h"

class Primitive : public GameComponent
{
public:
	enum ShapeID
	{
		pCircle,
		pAABB,
		pCount
	};
	
	Transform *pTrans;// position
	float radius;     // For circle
	Vector2 halfSize; // halfsize
	ShapeID Id;       // The Shape ID
	RigidBody *body;  // The rigidbody the collider is attached to
	PhysicsMaterial material;
	bool active;      // True for search


	void Initialize();
	void Update(float dt);
	void Release();

	Primitive();
	//Primitive(IEntity* Owner);
	//Primitive( ShapeID pID);

	virtual ~Primitive() = 0;
	virtual Primitive *Clone(void) const = 0;
	virtual void SetOrientation(float radians) const = 0;
	virtual ShapeID GetID(void) const = 0;


};

class Circle : public Primitive
{
public:

	Circle();
	//Circle(GameObjectComposition Owner);
	~Circle();

	void Initialize() ;
	void Update(float dt);
	void Release();

	Primitive *Clone(void) const
	{
		return new Circle();
	}

	void SetOrientation(float radians) const {}

	ShapeID GetID(void) const
	{
		return pCircle;
	}

};

class AABB : public Primitive
{
public:
	AABB();
	//AABB();
	~AABB();

	
	void Initialize() ;
	void Update(float dt) ;
	void Release() ;

	Primitive *Clone(void) const
	{
		return new AABB();
	}

	void SetOrientation(float radians) const {}

	ShapeID GetID(void) const
	{
		return pAABB;
	}

	void SetHalfSize(float width, float height)
	{
		halfSize.x = width;
		halfSize.y = height;

		vertexCount = 4;
		AABB_vertices[0].Set(-width, -height);
		AABB_vertices[1].Set(width, -height);
		AABB_vertices[2].Set(width, height);
		AABB_vertices[3].Set(-width, height);
	}

	int vertexCount;
	Vector2 AABB_vertices[4];
};

#endif