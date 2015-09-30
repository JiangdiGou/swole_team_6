//#include "our precompile header.h"
#include "Precompiled.h"
#include "primitive.h"
#include "../engineGraphics/debugDraw.h"
#include "../engineGraphics/Graphics.h"
//#include "../Component.h"

////// PRIMITIVE //////

Primitive::Primitive()
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
  pTrans = GetOwner()->has(Transform);
  body = GetOwner()->has(RigidBody);
	physics->colliders.push_back(this);
	//return true;
}

void Primitive::Update() {}
void Primitive::Release(){}


////// CIRCLE //////
Circle::Circle()
	
{
	radius = 1.01f;
	active = true;
	Id = pCircle;
}

Circle::~Circle(){}

void Circle::Initialize()
{
  pTrans = GetOwner()->has(Transform);
  body = GetOwner()->has(RigidBody);
	physics->colliders.push_back(this);
	//return true;
}

void Circle::Update(){
	Vector3 pos = pTrans->GetPosition();
	debugDrawCircle(glm::vec3(pos.x, pos.y, pos.z), radius, glm::vec3(0, 0, 0), 10);
}

void Circle::Release(){}

////// AABB //////
AABB::AABB()
{
	radius = 1.0f;
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
  body = GetOwner()->has(RigidBody);
	physics->colliders.push_back(this);
	//return true;
}
void AABB::Update(){
	Vector3 pos = pTrans->GetPosition();
	debugDrawSquare(glm::vec3(pos.x, pos.y, pos.z), halfSize.x, halfSize.y, glm::vec3(0,0,0));
}

void AABB::Release(){}

