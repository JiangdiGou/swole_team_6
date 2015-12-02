/*****************************************************************************/
/*!
\file    PhysicsManager.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
Main part for driving the physics engine works. Integrate with forces, 
velocity, gravity as well as solving the contacts.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

//#include "other stuff"
#include "PhysicsManager.h"
#include "Precompiled.h"
//#include "game setting file?"
//#include "Resolution.h"
//#include "math_utility.h"


Physics * PHYSICS = NULL;

Physics::Physics()
{
	//ErrorIf(PHYSICS != NULL, "Physics already initialized");
	PHYSICS = this;
	DebugDrawingActive = false;
	TimeAccumulation = 0.0f;
	Gravity = Vec2D(0, -5);
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
				if (Collsion.GenerateContacts((bodyA)->BodyShape, (bodyA)->Position, (bodyB)->BodyShape, (bodyB)->Position, &Contacts))
				{
          
          ShapeAAB* AShape = bodyA->GetOwner()->has(ShapeAAB);
          ShapeAAB* BShape = bodyB->GetOwner()->has(ShapeAAB);
          Collision collideEvent(AShape, BShape);

          //curCollisions.push_back(collideEvent);
          /*Collision ACollisionWith(BShape);
          Collision BCollisionWith(AShape);
          if (!bodyA->IsStatic)
          {
            //AllCollisions[nextCollisionIndex] = ACollisionWith;
            AShape->SendMessages(&AllCollisions[nextCollisionIndex]);
            nextCollisionIndex++;
          }
          if (!bodyB->IsStatic)
          {
            //AllCollisions[nextCollisionIndex] = BCollisionWith;
            BShape->SendMessages((Message*)&BCollisionWith);
            nextCollisionIndex++;
          }*/
				}
			}
		}
	}
}



void Physics::solveMessage()
{


	//Commit all physics updates
	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		(it)->solveMessage();
	}

	//Broadcast physics collision messages AFTER physics
	//has update the bodies
	/*for (unsigned i = 0; i < curCollisions.size(); ++i)
	{
    bool persist = false;
    for (unsigned j = 0; j < prevCollisions.size(); ++i)
    {
      if (curCollisions.at(i).firstObj == prevCollisions.at(j).firstObj &&
        curCollisions.at(i).otherObj == prevCollisions.at(j).otherObj)
      {
        persist = true;
        if (((Body*)curCollisions.at(i).firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
        {
          CollisionPersisted persist(curCollisions.at(i).otherObj);
          curCollisions.at(i).firstObj->GetOwner()->SendMessages(&persist);
        }
        if (((Body*)curCollisions.at(i).otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
        {
          CollisionPersisted persist(curCollisions.at(i).firstObj);
          curCollisions.at(i).otherObj->GetOwner()->SendMessages(&persist);
        }
      }
    }
    if (persist == false)
    {
      if (((Body*)curCollisions.at(i).firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionStarted start(curCollisions.at(i).otherObj);
        curCollisions.at(i).firstObj->GetOwner()->SendMessages(&start);
      }
      if (((Body*)curCollisions.at(i).otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionStarted start(curCollisions.at(i).firstObj);
        curCollisions.at(i).otherObj->GetOwner()->SendMessages(&start);
      }
    }
	}

  for (unsigned i = 0; prevCollisions.size(); ++i)
  {
    bool ended = true;
    for (unsigned j = 0; j < curCollisions.size(); ++i)
    {
      ended = false;
    }
    if (ended)
    {
      if (((Body*)curCollisions.at(i).firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionEnded end(curCollisions.at(i).otherObj);
        curCollisions.at(i).firstObj->GetOwner()->SendMessages(&end);
      }
      if (((Body*)curCollisions.at(i).otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionEnded end(curCollisions.at(i).firstObj);
        curCollisions.at(i).otherObj->GetOwner()->SendMessages(&end);
      }
    }
  }*/

 /* prevCollisions.clear();
  for (unsigned i = 0; i < curCollisions.size(); i++)
  {
    prevCollisions.at(i) = curCollisions.at(i);
  }*/
}

void Physics::Step(float dt)
{

	IntegrateBodies(dt);

	Contacts.Reset();

	DetectContacts(dt);

	Contacts.ResolveContacts(dt);

	solveMessage();

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


void Physics::DebugDraw()
{
	for (BodyIterator it = Bodies.begin(); it != Bodies.end(); ++it)
	{
		it->DebugDraw();
	}
}

void Physics::SendMessage(Message * m)
{

};



