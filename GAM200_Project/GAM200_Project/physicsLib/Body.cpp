/*****************************************************************************/
/*!
\file    Body.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
the base rigidbody for the physics to do all the effects
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
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
	AccumulatedForce = Vec2D(0, 0);
	Acceleration = Vec2D(0, 0);
	Mass = 1.0f;
	InvMass = 0.0f;
	Damping = 0.9f;
	BodyShape = NULL;
	Friction = 0.0f;
	Restitution = 0.3f;
	IsStatic = false;
	IsGhost = false;
	
}

Body::~Body()
{
	PHYSICS->Bodies.erase(this);
}

void Body::Integrate(float dt)
{
	//no need to check static objects
	if (IsStatic)
		return;
	

	//Save the previous position
	PrevPosition = Position;
	ShapeAAB * debugbody = GetOwner()->has(ShapeAAB);
	Transform* ownerTrans = GetOwner()->has(Transform);
	//Integrate the position using Euler 
	Position = Position + Velocity * dt; //acceleration term is small
  ownerTrans->SetPosition(ownerTrans->GetPositionXY() + Velocity*dt);

	//Generate  acceleration
	Acceleration = PHYSICS->Gravity;
	Vec2D newAcceleration = AccumulatedForce * InvMass + Acceleration;

	//Integrate the velocity
	Velocity = Velocity + newAcceleration * dt;
	Velocity *= std::pow(Damping, dt);

	if (Vec2D::DotProduct(Velocity, Velocity) > PHYSICS->MaxVelocitySq)
	{
		Vec2D Normalize(Velocity);
		Velocity = Velocity * PHYSICS->MaxVelocity;
	}

	//Remove the force
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
  if (BodyShape == NULL)
  {
    ShapeAAB* ownerAAB = GetOwner()->has(ShapeAAB);
    if (ownerAAB != NULL)
    {
      BodyShape = ownerAAB;
      //ownerAAB->body = this;
	
    }
  }
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

	//BodyShape->body = this;

}

void Body::SerializeRead(Serializer& str)
{
  StreamRead(str, Position);
  StreamRead(str, PrevPosition);
  StreamRead(str, Velocity);
  StreamRead(str, Mass);
  StreamRead(str, InvMass);
  StreamRead(str, Damping);
  StreamRead(str, Acceleration);
  //StreamRead(str, BodyShape);
  StreamRead(str, Friction);
  StreamRead(str, Restitution);
  StreamRead(str, IsStatic);
  StreamRead(str, IsGhost);
  StreamRead(str, AccumulatedForce);
  
}
void Body::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
  StreamWrite(str, Position);
  StreamWrite(str);
  StreamWrite(str, PrevPosition);
  StreamWrite(str);
  StreamWrite(str, Velocity);
  StreamWrite(str);
  StreamWrite(str, Mass);
  StreamWrite(str);
  StreamWrite(str, InvMass);
  StreamWrite(str);
  StreamWrite(str, Damping);
  StreamWrite(str);
  StreamWrite(str, Acceleration);
  StreamWrite(str);
  //StreamWrite(str, BodyShape);
  //StreamWrite(str);
  StreamWrite(str, Friction);
  StreamWrite(str);
  StreamWrite(str, Restitution);
  StreamWrite(str);
  StreamWrite(str, IsStatic);
  StreamWrite(str);
  StreamWrite(str, IsGhost);
  StreamWrite(str);
  StreamWrite(str, AccumulatedForce);
  StreamWrite(str);
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

float Body::DetermineRestitution(Body * a)
{
	return 	std::min(a->Restitution, this->Restitution);
}

float Body::DetermineFriction(Body * a)
{
	return sqrt(a->Friction * this->Friction);
}

void Body::ResolveCollision(ManifoldSet * contact, Body * a)
{
	
	contact->Bodies[0] = a;
	contact->Bodies[1] = this;
	contact->Restitution = DetermineRestitution(this);
	contact->FrictionCof = DetermineFriction(this);
}

ZilchDefineType(Body, "Body", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindConstructor(builder, type, Body, ZilchNoNames);
  ZilchBindDestructor(builder, type, Body);

  ZilchBindMethod(builder, type, &Body::AddForce, ZilchNoOverload, "AddForce", ZilchNoNames);

  ZilchBindMethod(builder, type, &Body::SetPosition, ZilchNoOverload, "SetPosition", ZilchNoNames);
  ZilchBindMethod(builder, type, &Body::SetVelocity, ZilchNoOverload, "SetVelocity", ZilchNoNames);
  //ZilchBindMethod(builder, type, &Body::AddForce, ZilchNoOverload, "AddForce", ZilchNoNames);

  ZilchBindField(builder, type, &Body::Position, "Position", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Velocity, "Velocity", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Acceleration, "Acceleration", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Mass, "Mass", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::InvMass, "InvMass", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Restitution, "Restitution", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Friction, "Friction", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::Damping, "Damping", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::AccumulatedForce, "AccumulatedForce", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::IsStatic, "IsStatic", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Body::IsGhost, "IsGhost", PropertyBinding::GetSet);

}