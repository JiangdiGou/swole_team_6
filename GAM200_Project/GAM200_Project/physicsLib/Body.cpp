#include "our header files"
#include "Body.h"

float Random(float low, float high)
{
  float a = (float)rand();
  a /= RAND_MAX;
  a = (high-low)*a + low;
  return a;
}

RigidBody::RigidBody(IEntity* Owner, Primitive *shape) : 
  IComponent(Component_Type::CT_Body, Owner), bodyShape(shape->Clone())
{
  bodyShape->body = this;
  bodyShape->radius = shape->radius;
  bodyShape->halfSize.x = shape->halfSize.x;
  bodyShape->halfSize.y = shape->halfSize.y;
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
  orientation = Random(-PI,PI);
  /*stFric = 0.5f;
  dynFric = 0.3f;
  friction = 0.2f;*/
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
  // delete the body list
  //physics->bodies.clear();
    
	//Let's say if we have physics manager
    for (auto iter = physics->bodies.begin(); iter != physics->bodies.end(); ++iter)
    {
        if (*iter == this)
        {
            physics->bodies.erase(iter);
            return;
        }
    }
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

    // Calculate inertia
    if (bodyShape->Id == Primitive::pAABB)
    {
      inertia = mass * (bodyShape->halfSize.x * bodyShape->halfSize.x +
      bodyShape->halfSize.y * bodyShape->halfSize.y);
      invInertia = 1.0f / inertia;

    }
    else if (bodyShape->Id == Primitive::pCircle)
    {
      inertia = mass * bodyShape->radius * bodyShape->radius;
      invInertia = 1.0f/inertia;
    }
  }

}

bool RigidBody::Initialize()
{
  pTrans = Owner->GetTransform();

  position.x = pTrans->position.x;
  position.y = pTrans->position.y;

  physics->bodies.push_back(this);
  return true;
}

void RigidBody::Update(float dt)
{
  pTrans->SetPosition(position);
}

void RigidBody::Release(){}

void RigidBody::setPosition(const Vector2 &position)
{
  this->position = position;
}

void RigidBody::setPosition(const float x, const float y)
{
  position.x = x;
  position.y = y;

}

Vector2 RigidBody::getPosition() const
{
  return position;
}

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

//void RigidBody::SetStatic(void)
//{
//  // Sets the object to static
//  isStatic = true;
//
//  mass = 0.0f;
//  invMass = 0.0f;
//  inertia = 0.0f;
//  invInertia = 0.0f;
//  
//}

void RigidBody::ApplyImpulse(const Vector2& impulse, const Vector2D& contactVec)
{
  velocity += invMass * impulse;
  angularVelocity += invInertia * Vector2D::CrossProduct(contactVec, impulse);
}

void RigidBody::SetOrientation(float radians)
{
  orientation = radians;
  bodyShape->SetOrientation(radians);
}

//void RigidBody::Trigger(IEntity *collObj)
//{
//  if (triggerCallbacks.size() > 0)
//    triggerCallbacks[0]->OnCollision(collObj);
//  //I forget what I did here, but it looks like only the first callback to be registered is used
//  /*for (auto it : triggerCallbacks)
//  {
//    it->OnCollision(collObj);
//  }*/
//}

//void RigidBody::AddTriggerCallback(CollisionDelegate *obj)
//{
//  triggerCallbacks.push_back(obj);
//}

bool RigidBody::IsStatic()
{
  return isStatic;
}

bool RigidBody::CheckDetectsCollision()
{
  return isGhost;
}

void RigidBody::MovePosition &pos)
{
  position = pos;
}

void RigidBody::SetDensity(float density)
{
  // This is useful to set the mass to a value 
  // which scales with the size of the colliders.
  // D/V = M

  if (bodyShape->GetID() == Primitive::pCircle)
  {
    // Circle pi*r^2
    mass = PI * (bodyShape->radius * bodyShape->radius);
    invMass = 1.0f / mass;

  }
  else if (bodyShape->GetID() == Primitive::pAABB)
  {
    // AABB A * b
    mass = (bodyShape->halfSize.x + bodyShape->halfSize.x) *
           (bodyShape->halfSize.y + bodyShape->halfSize.y);
    invMass = 1.0f / mass; // Need to check if mass is not zero
  }
  

}