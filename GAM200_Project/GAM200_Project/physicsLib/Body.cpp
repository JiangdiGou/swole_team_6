//#include "our header files"
#include "Precompiled.h"
#include "Transform.h"
//#include "../Composition.h"
float Random(float low, float high)
{
  float a = (float)rand();
  a /= RAND_MAX;
  a = (high-low)*a + low;
  return a;
}

RigidBody::RigidBody()
{
  
  restitution = 0.2f;
  velocity.Clear();
  acceleration.Clear();
  setRotation(0.0f);
  // By default mass is set to 1.0f
  setMass(1.0f);
  invMass = getInvMass();
  //inertia = mass * shape->radius * shape->radius;
  // By default inertia is set to 1.0f
  inertia = 1.0f;
  invInertia = 1.0f/inertia;
  isStatic = false;
  angularVelocity = 0.0f;
  orientation = Random(-FLOAT_PI, FLOAT_PI);
  isGhost = false;
  useGravity = true; // By default set gravity to on
  isKinematic = false;

  if (inertia)
  {
      float check = inertia;

      printf(" %f ", check);
  
  }
}

RigidBody::~RigidBody()
{
  
}

void RigidBody::set(float mass_num)
{
  // Set mass, inverse mass, inertia, and inverse inertia
  if (mass_num == 0.0f)
  {
    SetStatic();
  }
  else
  {
    mass = mass_num;
    invMass = 1.0f/mass;

    //// Calculate inertia
	AABB* shapeAABB = GetOwner()->has(AABB);
	Circle* shapeCircle = GetOwner()->has(Circle);
    if (shapeAABB != NULL)
    {
	  inertia = mass * (shapeAABB->halfSize.x * shapeAABB->halfSize.x +
	    shapeAABB->halfSize.y * shapeAABB->halfSize.y);
      invInertia = 1.0f / inertia;

    }
	else if (shapeCircle != NULL)
    {
	  inertia = mass * shapeCircle->radius * shapeCircle->radius;
      invInertia = 1.0f/inertia;
    }
  }

}

void RigidBody::Initialize()
{
	pTrans = GetOwner()->has(Transform);


  physics->bodies.push_back(this);
  //return true;
}

void RigidBody::Update()
{
  /*pTrans->SetPosition(position);*/
}
void RigidBody::SendMessages(Message * message)
{
  switch (message->MessageId)
  {
    // The user has pressed a (letter/number) key, we may respond by creating
    // a specific object based on the key pressed.
  case Mid::CharacterKey:
  {
    MessageCharacterKey* messageChar = (MessageCharacterKey*)message;
    switch (messageChar->character)
    {
    case 'a':
    {
      setVelocity(1.5, getVelocity().y);
    }
    }
  }
  }
}
void RigidBody::Release(){}

//void RigidBody::setPosition(const float x, const float y)
//{
//  //positi
//
//}

void RigidBody::setAcceleration(const Vector2 &acc)
{
  acceleration = acc;
}

void RigidBody::setAcceleration(const float x, const float y)
{
  acceleration.x = x;
  acceleration.y = y;
}

Vector2 RigidBody::getAcceleration() const
{
  return acceleration;
}

void RigidBody::setVelocity(const Vector2 &velocity)
{
  RigidBody::velocity = velocity;
}

void RigidBody::setVelocity(const float x, const float y)
{
  velocity.x = x;
  velocity.y = y;
}

Vector2 RigidBody::getVelocity() const
{
  return velocity;
}
void RigidBody::setMass(const float m)
{
  mass = m;
}

float RigidBody::getMass() const
{
  return mass;
}

float RigidBody::getInvMass() const
{
  return (1.0f/mass);
}

void RigidBody::setRotation(const float rot)
{
  rotation = rot;
}

float RigidBody::getRotation() const
{
  return rotation;
}

void RigidBody::AddForce(const Vector2 &force)
{
  forceAccum += force;
}

void RigidBody::SetStatic(void)
{
  // Sets the object to static
  isStatic = true;

  mass = 0.0f;
  invMass = 0.0f;
  inertia = 0.0f;
  invInertia = 0.0f;
  
}

void RigidBody::ApplyImpulse(const Vector2& impulse, const Vec2D& contactVec)
{
  velocity += invMass * impulse;
  angularVelocity += invInertia * Vec2D::CrossProduct(contactVec, impulse);
}

void RigidBody::SetOrientation(float radians)
{
  orientation = radians;
  //bodyShape->SetOrientation(radians);
}

void RigidBody::Trigger(GameObjectComposition *collObj)
{
  if (triggerCallbacks.size() > 0)
    triggerCallbacks[0]->OnCollision(collObj);
  //I forget what I did here, but it looks like only the first callback to be registered is used
  /*for (auto it : triggerCallbacks)
  {
    it->OnCollision(collObj);
  }*/
}

void RigidBody::AddTriggerCallback(CollisionDelegate *obj)
{
  triggerCallbacks.push_back(obj);
}

bool RigidBody::IsStatic()
{
  return isStatic;
}

bool RigidBody::CheckDetectsCollision()
{
  return isGhost;
}

void RigidBody::SetDensity(float density)
{
  // This is useful to set the mass to a value 
  // which scales with the size of the colliders.
  // D/V = M
	AABB* shapeAABB = GetOwner()->has(AABB);
	Circle* shapeCircle = GetOwner()->has(Circle);
	if (shapeCircle->GetID() == Primitive::pCircle)
  {
    // Circle pi*r^2
		mass = FLOAT_PI * (shapeCircle->radius * shapeCircle->radius);
    invMass = 1.0f / mass;

  }
	else if (shapeAABB->GetID() == Primitive::pAABB)
  {
    // AABB A * b
		mass = (shapeAABB->halfSize.x + shapeAABB->halfSize.x) *
			(shapeAABB->halfSize.y + shapeAABB->halfSize.y);
    invMass = 1.0f / mass; // Need to check if mass is not zero
  }
  

}