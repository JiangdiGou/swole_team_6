/*****************************************************************************/
/*!
\file    Body.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the base rigidbody for the physics to do all the effects
\remarks


All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

//#include "our header files"
//#include "Precompiled.h"
#include "Transform.h"
#include "Body.h"
#include "PhysicsManager.h"
//#include "../Composition.h"
float Random(float low, float high)
{
  float a = (float)rand();
  a /= RAND_MAX;
  a = (high-low)*a + low;
  return a;
}


Body::Body()
{
	Position = Vec2D(0, 0);
	PrevPosition = Vec2D(0, 0);
	Velocity = Vec2D(0, 0);
	Mass = 0.0f;
	InvMass = 0.0f;
	Damping = 0.9f;
	Acceleration = Vec2D(0, 0);
	BodyShape = NULL;
	Friction = 0.0f;
	Restitution = 0.0f;
	IsStatic = false;
	IsGhost = false;
	AccumulatedForce = Vec2D(0, 0);
}

Body::~Body()
{
	delete BodyShape;
	PHYSICS->Bodies.erase(this);
}

void Body::Integrate(float dt)
{
	//Do not integrate static bodies
	if (IsStatic) return;
	

	//Store prev position
	PrevPosition = Position;
	ShapeAAB * debugbody = GetOwner()->has(ShapeAAB);
	Transform* ownerTrans = GetOwner()->has(Transform);
	//Integrate the position using Euler 
	Position = Position + Velocity * dt; //acceleration term is small
  ownerTrans->SetPosition(ownerTrans->GetPositionXY() + Velocity*dt);

	//Determine the acceleration
	Acceleration = PHYSICS->Gravity;
	Vec2D newAcceleration = AccumulatedForce * InvMass + Acceleration;

	//Integrate the velocity
	Velocity = Velocity + newAcceleration * dt;

	//Dampen the velocity for numerical stability and soft drag
	Velocity *= std::pow(Damping, dt);

	//Clamp to velocity max for numerical stability
	if (Vec2D::DotProduct(Velocity, Velocity) > PHYSICS->MaxVelocitySq)
	{
		Vec2D Normalize(Velocity);
		Velocity = Velocity * PHYSICS->MaxVelocity;
	}

	//Clear the force
	AccumulatedForce = Vec2D(0, 0);

	debugDrawSquare(ownerTrans->GetPosition(), 2*debugbody->Extents.x, 2*debugbody->Extents.y, Vector3(0, 0, 0));
	
}

void Body::solveMessage()
{
	bodyTrans->GetPositionXY() = Position;
}

bool Body::CheckDetectsCollision()
{
  return IsGhost;
}

void Body::DebugDraw()
{

}

void Body::Initialize()
{
	//Get the transform to write results to
	bodyTrans = GetOwner()->has(Transform);

	//Get the starting position
	Position = bodyTrans->GetPositionXY();

	//Add this body to the body list
	PHYSICS->Bodies.push_back(this);

	//If mass is zero object is interpreted
	//to be static
	if (Mass > 0.0f)
	{
		IsStatic = false;
		InvMass = 1.0f / Mass;
	}
	else
	{
		IsStatic = true;
		InvMass = 0.0f;
	}

	BodyShape->body = this;
}

void Body::AddForce(Vec2D force)
{
	AccumulatedForce += force;
}

void Body::SetPosition(Vec2D p)
{
	Position = p;
	bodyTrans->SetPosition(p);
}

void Body::SetVelocity(Vec2D v)
{
	Velocity = v;
}



//RigidBody::RigidBody(/*Primitive*shape*/) //: bodyShape(shape->Clone())
//{
//	/*bodyShape->body = this;
//	bodyShape->radius = shape->radius;
//	bodyShape->halfSize.x = shape->halfSize.x;
//	bodyShape->halfSize.y = shape->halfSize.y;*/
//  restitution = 0.2f;
//  velocity.Clear();
//  acceleration.Clear();
//  setRotation(0.0f);
//  // By default mass is set to 1.0f
//  setMass(1.0f);
//  invMass = getInvMass();
//  //inertia = mass * shape->radius * shape->radius;
//  // By default inertia is set to 1.0f
//  inertia = 1.0f;
//  invInertia = 1.0f/inertia;
//  isStatic = false;
//  angularVelocity = 0.0f;
//  orientation = Random(-FLOAT_PI, FLOAT_PI);
//  isGhost = false;
//  useGravity = true; // By default set gravity to on
//  isKinematic = false;
//
//  if (inertia)
//  {
//      float check = inertia;
//
//      printf(" %f ", check);
//  
//  }
//}
//
//RigidBody::~RigidBody()
//{
//  
//}
//
//void RigidBody::set(float mass_num)
//{
//  // Set mass, inverse mass, inertia, and inverse inertia
//  if (mass_num == 0.0f)
//  {
//    SetStatic();
//  }
//  else
//  {
//    mass = mass_num;
//    invMass = 1.0f/mass;
//
//    //// Calculate inertia
//	AABB* shapeAABB = GetOwner()->has(AABB);
//	Circle* shapeCircle = GetOwner()->has(Circle);
//    if (shapeAABB != NULL)
//    {
//	  inertia = mass * (shapeAABB->halfSize.x * shapeAABB->halfSize.x +
//	    shapeAABB->halfSize.y * shapeAABB->halfSize.y);
//      invInertia = 1.0f / inertia;
//
//    }
//	else if (shapeCircle != NULL)
//    {
//	  inertia = mass * shapeCircle->radius * shapeCircle->radius;
//      invInertia = 1.0f/inertia;
//    }
//  }
//
//}
//
//void RigidBody::Initialize()
//{
//	pTrans = GetOwner()->has(Transform);
//	/*position.x = pTrans->position.x;
//	position.y = pTrans->position.y;*/
//
//	//physics->bodies.push_back(this);
//
//  physics->bodies.push_back(this);
//  //return true;
//}
//
//void RigidBody::Update(float dt)
//{
//	//pTrans->SetPosition(position);
//  /*pTrans->SetPosition(position);*/
//}
//void RigidBody::SendMessages(Message * message)
//{
//  switch (message->MessageId)
//  {
//    // The user has pressed a (letter/number) key, we may respond by creating
//    // a specific object based on the key pressed.
//  case Mid::CharacterKey:
//  {
//    MessageCharacterKey* messageChar = (MessageCharacterKey*)message;
//    switch (messageChar->character)
//    {
//    case 'd':
//    {
//      setVelocity(0.5, 0);
//    }
//	case 'a':
//	{
//		setVelocity(-0.5, 0);
//	}
//    }
//  }
//  }
//}
//void RigidBody::Release(){}

//void RigidBody::setPosition(const float x, const float y)
//{
//  //positi
//
//}

//void RigidBody::setPosition(const Vector2 &position)
//{
//	this->position = position;
//}
//
//void RigidBody::setPosition(const float x, const float y)
//{
//	position.x = x;
//	position.y = y;
//
//}
//
//Vector2 RigidBody::getPosition() const
//{
//	return position;
//}

//void RigidBody::setAcceleration(const Vector2 &acc)
//{
//  acceleration = acc;
//}
//
//void RigidBody::setAcceleration(const float x, const float y)
//{
//  acceleration.x = x;
//  acceleration.y = y;
//}
//
//Vector2 RigidBody::getAcceleration() const
//{
//  return acceleration;
//}
//
//void RigidBody::setVelocity(const Vector2 &velocity)
//{
//  RigidBody::velocity = velocity;
//}
//
//void RigidBody::setVelocity(const float x, const float y)
//{
//  velocity.x = x;
//  velocity.y = y;
//}
//
//Vector2 RigidBody::getVelocity() const
//{
//  return velocity;
//}
//void RigidBody::setMass(const float m)
//{
//  mass = m;
//}
//
//float RigidBody::getMass() const
//{
//  return mass;
//}
//
//float RigidBody::getInvMass() const
//{
//  return (1.0f/mass);
//}
//
//void RigidBody::setRotation(const float rot)
//{
//  rotation = rot;
//}
//
//float RigidBody::getRotation() const
//{
//  return rotation;
//}
//
//void RigidBody::AddForce(const Vector2 &force)
//{
//  forceAccum += force;
//}
//
//void RigidBody::SetStatic(void)
//{
//  // Sets the object to static
//  isStatic = true;
//
//  velocity.x = 0.0f;
//  velocity.y = 0.0f;
//  mass = 0.0f;
//  invMass = 0.0f;
//  inertia = 0.0f;
//  invInertia = 0.0f;
//  
//}
//
//void RigidBody::ApplyImpulse(const Vector2& impulse, const Vec2D& contactVec)
//{
//  velocity += invMass * impulse;
//  angularVelocity += invInertia * Vec2D::CrossProduct(contactVec, impulse);
//}
//
//void RigidBody::SetOrientation(float radians)
//{
//  orientation = radians;
//  //bodyShape->SetOrientation(radians);
//}
//
//void RigidBody::Trigger(GameObjectComposition *collObj)
//{
//  if (triggerCallbacks.size() > 0)
//    triggerCallbacks[0]->OnCollision(collObj);
//  //I forget what I did here, but it looks like only the first callback to be registered is used
//  /*for (auto it : triggerCallbacks)
//  {
//    it->OnCollision(collObj);
//  }*/
//}
//
//void RigidBody::AddTriggerCallback(CollisionDelegate *obj)
//{
//  triggerCallbacks.push_back(obj);
//}
//
//bool RigidBody::IsStatic()
//{
//  return isStatic;
//}
//
//bool RigidBody::CheckDetectsCollision()
//{
//  return isGhost;
//}
//
//void RigidBody::SetDensity(float density)
//{
//  // This is useful to set the mass to a value 
//  // which scales with the size of the colliders.
//  // D/V = M
//	AABB* shapeAABB = GetOwner()->has(AABB);
//	Circle* shapeCircle = GetOwner()->has(Circle);
//	if (shapeCircle->GetID() == Primitive::pCircle)
//  {
//    // Circle pi*r^2
//		mass = FLOAT_PI * (shapeCircle->radius * shapeCircle->radius);
//    invMass = 1.0f / mass;
//
//  }
//	else if (shapeAABB->GetID() == Primitive::pAABB)
//  {
//    // AABB A * b
//		mass = (shapeAABB->halfSize.x + shapeAABB->halfSize.x) *
//			(shapeAABB->halfSize.y + shapeAABB->halfSize.y);
//    invMass = 1.0f / mass; // Need to check if mass is not zero
//  }
//  
//
//}