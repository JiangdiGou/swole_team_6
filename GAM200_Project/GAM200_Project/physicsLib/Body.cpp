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
	//delete BodyShape;
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

void Body::fuckCollision(ManifoldSet * contact, Body * a)
{
	
	//ManifoldSet * contact = c->GetNewContact();
	//Vec2D normal = positionDelta.x < 0 ? Vec2D(-1, 0) : Vec2D(1, 0);
	contact->Bodies[0] = a;
	contact->Bodies[1] = this;
	//contact->ContactNormal = normal;
	//contact->Penetration = xDiff;
	contact->Restitution = DetermineRestitution(this);
	contact->FrictionCof = DetermineFriction(this);
}
