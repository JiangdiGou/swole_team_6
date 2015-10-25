//#include "other stuff"
#include "PhysicsManager.h"
#include "Precompiled.h"
//#include "game setting file?"
//#include "Resolution.h"
//#include "math_utility.h"

//sample

Physics * PHYSICS = NULL;

Physics::Physics()
{
	//ErrorIf(PHYSICS != NULL, "Physics already initialized");
	PHYSICS = this;
	DebugDrawingActive = false;
	TimeAccumulation = 0.0f;
	Gravity = Vec2D(0, -1);
	MaxVelocity = 1000;
	MaxVelocitySq = MaxVelocity*MaxVelocity;
	PenetrationEpsilon = 0.2f;
	PenetrationResolvePercentage = 0.8f;
	StepModeActive = false;
	AdvanceStep = false;
}

void Physics::Initialize()
{
	
	//RegisterComponent(Body);
}

void Physics::IntegrateBodies(float dt)
{
	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		it->Integrate(dt);
	}
}

void Physics::DetectContacts(float dt)
{
	BodyIterator bodyA = Bodies.begin();
	BodyIterator lastBody = Bodies.last(); //end - 1

	//Broad phase should be added this is N^2
	for (; bodyA != lastBody; ++bodyA)
	{
		BodyIterator bodyB = bodyA;
		++bodyB;
		for (; bodyB != Bodies.end(); ++bodyB)
		{
			//Do not collide static bodies with other static bodies
			if (!bodyA->IsStatic || !bodyB->IsStatic)
			{
				Collsion.GenerateContacts((bodyA)->BodyShape, (bodyA)->Position, (bodyB)->BodyShape, (bodyB)->Position, &Contacts);
			}
		}
	}
}



void Physics::PublishResults()
{
	//Commit all physics updates
	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		(it)->PublishResults();
	}

	//Broadcast physics collision messages AFTER physics
	//has update the bodies
	for (unsigned i = 0; i<Contacts.NumberOfContacts; ++i)
	{
		BodyContact* contact = &Contacts.contactArray[i];
		MessageCollide messageCollide;
		messageCollide.ContactNormal = contact->ContactNormal;
		messageCollide.Impulse = contact->ContactImpulse;
		messageCollide.CollidedWith = contact->Bodies[1]->GetOwner();
		contact->Bodies[0]->GetOwner()->SendMessages(&messageCollide);
		if (contact->Bodies[1] != NULL)
		{
			messageCollide.ContactNormal = -contact->ContactNormal;
			messageCollide.Impulse = contact->ContactImpulse;
			messageCollide.CollidedWith = contact->Bodies[0]->GetOwner();
			contact->Bodies[1]->GetOwner()->SendMessages(&messageCollide);
		}
	}
}

void Physics::Step(float dt)
{

	IntegrateBodies(dt);

	Contacts.Reset();

	DetectContacts(dt);

	Contacts.ResolveContacts(dt);

	PublishResults();

}

void Physics::Update(float dt)
{
	const float TimeStep = 1.0f / 60.0f;

	if (!StepModeActive)
	{
		TimeAccumulation += dt;
		TimeAccumulation = std::min(TimeAccumulation, TimeStep * 5);
		if (TimeAccumulation > TimeStep)
		{
			TimeAccumulation -= TimeStep;
			Step(TimeStep);
		}

	}
	else
	{
		TimeAccumulation = 0.0f;
		if (AdvanceStep)
		{
			Step(TimeStep);
			AdvanceStep = false;
		}
	}

	if (DebugDrawingActive)
		DebugDraw();

}

//GOC * Physics::TestPoint(Vec2 testPosition)
//{
//	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
//	{
//		if (it->BodyShape->TestPoint(testPosition))
//			return it->GetOwner();
//	}
//
//	return NULL;
//}

void Physics::DebugDraw()
{
	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		it->DebugDraw();
	}
}

void Physics::SendMessage(Message * m)
{
	//if (m->MessageId == Mid::ToggleDebugInfo)
	//{
	//	ToggleDebugDisplay * debugM = (ToggleDebugDisplay*)m;
	//	DebugDrawingActive = debugM->DebugActive;
	//}
};



//PhysicsManager *physics;
//
//
//
////MOVEMENT COLLISION FORCESS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//PhysicsManager::PhysicsManager()// : ISystem("Physics", SystemType::ST_Physics)
//{
//  physics = this;
//  TimeAccumulation = 0.0f;
//  Gravity = Vec2D(0, -.5);
//  MaxVelocity = 1000;
//  MaxVelocitySq = MaxVelocity*MaxVelocity;
//  PenetrationEpsilon = 0.2f;
//  PenetrationResolvePercentage = 0.8f;
//  StepModeActive = false;
//  AdvanceStep = false;
////	float *temp = NULL;
////	GlobalSettings->GetFloatValue("___ PHYSICS SETTINGS ___", temp, false);
////	GlobalSettings->GetFloatValue("Gravity", GRAVITY, true);
//}
//
//PhysicsManager::~PhysicsManager()
//{
//}
//
//void PhysicsManager::Initialize()
//{
//}
//
//void PhysicsManager::Update(float dt)
//{
//	Step(dt);
//}
//
//void PhysicsManager::Shutdown()
//{
//	colliders.clear();
//	bodies.clear();
//}
//
//void PhysicsManager::ColliderCheck()
//{
//	//  COLLIDER LIST
//	for (unsigned int i = 0; i < colliders.size(); ++i)
//	{
//		if (colliders[i] == NULL)
//		{
//			continue;
//		}
//
//		Primitive *a = colliders[i];
//
//		for (unsigned int j = i + 1; j < colliders.size(); ++j)
//		{
//			Primitive *b = colliders[j];
//
//			if (a->active == false && b->active == false)
//			{
//				continue;
//			}
//			Transform* transA = a->GetOwner()->has(Transform);
//			Vector3 posA = transA->GetPosition();
//			Transform* transB = b->GetOwner()->has(Transform);
//			Vector3 posB = transB->GetPosition();
//
//			if (a->Id == Primitive::pCircle && b->Id == Primitive::pCircle)
//			{
//				if (CollisionChecker::CircleAndCircle(reinterpret_cast<Circle *>(a), posA, reinterpret_cast<Circle *>(b), posB))
//				{
//					printf("Circle\n");
//				}
//			}
//			else if (a->Id == Primitive::pAABB && b->Id == Primitive::pAABB)
//			{
//				if (CollisionChecker::AABBAndAABB(reinterpret_cast<AABB *>(a), posA, reinterpret_cast<AABB *>(b), posB))
//				{
//					printf("AABB\n");
//					//We get to this point twice for one collision, right? If so, only need this one call.
//					reinterpret_cast<RigidBody*>((a->GetOwner())->GetComponent(CT_RigidBody));//->Trigger(b->GetOwner());
//					reinterpret_cast<RigidBody*>((b->GetOwner())->GetComponent(CT_RigidBody));//->Trigger(a->GetOwner());
//
//				}
//			}
//			else if (a->Id == Primitive::pAABB && b->Id == Primitive::pCircle)
//			{
//				if (CollisionChecker::AABBAndCircle(reinterpret_cast<AABB *>(a), posA, reinterpret_cast<Circle *>(b), posB))
//				{
//					printf("AABB to Circle\n");
//				}
//			}
//			else if (a->Id == Primitive::pCircle && b->Id == Primitive::pAABB)
//			{
//				if (CollisionChecker::CircleAndAABB(reinterpret_cast<Circle *>(a), posA, reinterpret_cast<AABB *>(b), posB))
//				{
//					printf("Circle to AABB\n");
//				}
//			}
//		}
//	}
//}
//
//
//void PhysicsManager::RigidBodyCheck()
//{
//	// Go through the bodies
//	for (unsigned int i = 0; i < colliders.size(); ++i)
//	{
//		if (colliders[i] == NULL)
//		{
//			continue;
//		}
//
//		Primitive *a = colliders[i];
//
//		// Loop through the next body
//		for (unsigned int j = i + 1; j < bodies.size(); ++j)
//		{
//			Primitive *b = colliders[j];
//
//			// Check if these object are static
//			if (a->body->isStatic == true && b->body->isStatic == true)
//			{
//				continue;
//			}
//
//			//// Set manifold data
//			Manifold m(a, b);
//
//			//// Solve
//			m.Solve();
//
//			//Check if there's any contact count
//			if (m.contactCount)
//			{
//				// Append new element to the end
//				contacts.emplace_back(m);
//			}
//		}
//	}
//}
//void PhysicsManager::Step(float dt)
//{
//
//	ColliderCheck();
//
//	// Clear any old information in the vector
//	contacts.clear();
//
//	RigidBodyCheck();
//	//if (body->isStatic)
//
//	// Integrate forces
//	for (unsigned int i = 0; i < bodies.size(); ++i)
//	{
//		IntegrateForces(bodies[i], dt);
//	}
//
//	// Pre-Steps
//	for (unsigned int i = 0; i < contacts.size(); ++i)
//	{
//		contacts[i].PreStep(dt);
//	}
//
//
//	//Solve collisions
//	for (int j = 0; j < 10; ++j)
//	{
//		for (unsigned int i = 0; i < contacts.size(); ++i)
//		{
//			contacts[i].AppyImpulse();
//		}
//	}
//
//	// Integrate Velocities
//	for (unsigned int i = 0; i < bodies.size(); ++i)
//	{
//		IntegrateVelocity(bodies[i], dt);
//	}
//
//
//
//	//Correct Positions
//	for (unsigned int i = 0; i < contacts.size(); ++i)
//	{
//		contacts[i].CorrectPosition();
//	}
//
//	// Clear forces
//	for (unsigned int i = 0; i < bodies.size(); ++i)
//	{
//		RigidBody *b = bodies[i];
//		b->forceAccum.Clear();
//		
//	}
//
//	/*for (unsigned int i = 0; i < bodies.size(); ++i)
//	{
//		bodies[i]->Update(dt);
//	}*/
//}
//
//void PhysicsManager::IntegrateForces(RigidBody *body, float dt)
//{
//	// Skip if static
//	if (body->isStatic == true)
//	{
//		return;
//	}
//
//	if (body->useGravity)
//	{
//		// Symplectic Euler w/ gravity
//        Vec2D gravityY = (body->forceAccum * body->invMass + Vec2D(0, GRAVITY)) * (dt / 2.0f);
//		body->setVelocity(body->getVelocity() + gravityY);
//		//body->velocity.x += GRAVITY;
//		
//	}
//	else
//	{
//		// Without gravity
//		Vec2D correctionY = ((body->forceAccum * body->invMass) * (dt / 2.0f));
//		body->setVelocity(body->getVelocity() + correctionY);
//		std::cout << body->getVelocity().x << "vx" << std::endl;
//	}
//}
//
//void PhysicsManager::IntegrateVelocity(RigidBody *body, float dt)
//{
//	// Skip if static
//	if (body->isStatic == true)
//	{
//		return;
//	}
//  Vector2 positionXY = body->pTrans->GetPositionXY();
//  body->pTrans->SetPosition(positionXY + body->getVelocity() *dt);
//	body->orientation += body->angularVelocity * dt;
//	body->SetOrientation(body->orientation);
//	IntegrateForces(body, dt);
//}
