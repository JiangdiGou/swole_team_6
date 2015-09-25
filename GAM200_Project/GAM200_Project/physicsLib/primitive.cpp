//#include "our precompile header.h"
#include "primitive.h"
//#include "../Component.h"

////// PRIMITIVE //////
Primitive::Primitive( ShapeID pID,ComponentTypeId type)
	: Id(pID)
{
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
//Circle::Circle()
//	: Primitive(nullptr, pCircle,
//CT_CircleCollider)
//{
//
//}
//
//Circle::Circle()
//	//: Primitive(Owner, pCircle, Component_Type::CT_CircleCollider)
//{
//}
//
//Circle::~Circle(){}
//
//void Circle::Initialize()
//{
//	pTrans = GetOwner()->has(Transform);
//	physics->colliders.push_back(this);
//	//return true;
//}
//
//void Circle::Update(float dt){}
//
//void Circle::Release(){}
//
//////// AABB //////
//AABB::AABB()
//{
//	GetOwner()->has(BoxCollider);
//}
//
//AABB::AABB(GameObject Owner)
//	: Primitive(Owner, pAABB, Component_Type::CT_BoxCollider)
//{
//
//}
//AABB::~AABB()
//{
//}
//
//void AABB::Initialize()
//{
//	pTrans = GetOwner()->has(Transform);
//	physics->colliders.push_back(this);
//	//return true;
//}
//void AABB::Update(float dt){}
//
//void AABB::Release(){}

