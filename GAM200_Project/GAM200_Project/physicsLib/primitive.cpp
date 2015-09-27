//#include "our precompile header.h"
#include "Precompiled.h"
#include "primitive.h"
//#include "../Component.h"

////// PRIMITIVE //////

Primitive::Primitive()
{
	pTrans = GetOwner()->has(Transform);
	body = GetOwner()->has(RigidBody);
	radius = 0.0f;
	active = true; //false;
}

Primitive::~Primitive()
{
	for (auto iter = physics->colliders.begin(); iter != physics->colliders.end(); ++iter)
	{
		if (*iter == this)
		{
			physics->colliders.erase(iter);
			return;
		}
	}
}

void Primitive::Initialize()
{
	physics->colliders.push_back(this);
	//return true;
}

void Primitive::Update(float dt) {}
void Primitive::Release(){}


////// CIRCLE //////
Circle::Circle()
	
{
	radius = 0.0f;
	active = true;
	Id = pCircle;
}

Circle::~Circle(){}

void Circle::Initialize()
{
	pTrans = GetOwner()->has(Transform);
	physics->colliders.push_back(this);
	//return true;
}

void Circle::Update(float dt){}

void Circle::Release(){}

////// AABB //////
AABB::AABB()
{
	radius = 0.0f;
	active = true;
	Id = pAABB;
	//GetOwner()->has(BoxCollider);
}


AABB::~AABB()
{
}

void AABB::Initialize()
{
	pTrans = GetOwner()->has(Transform);
	physics->colliders.push_back(this);
	//return true;
}
void AABB::Update(float dt){}

void AABB::Release(){}

