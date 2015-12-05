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
	PHYSICS = this;
	TimeAccumulation = 0.0f;
	Gravity = Vec2D(0, -5);
	MaxVelocity = 1000;
	MaxVelocitySq = MaxVelocity*MaxVelocity;
	PenetrationEpsilon = 0.2f;
	PenetrationResolvePercentage = 0.8f;
	StepModeActive = false;
	AdvanceStep = false;
}

void Physics::Reload()
{
  while (prevCollisions.size())
  {
    delete prevCollisions.back();
    prevCollisions.pop_back();
  }
  while (curCollisions.size())
  {
    delete curCollisions.back();
    curCollisions.pop_back();
  }
  Contacts.Reset();
  while (Bodies.begin())
    Bodies.pop_front();
}

void Physics::Initialize()
{

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
	BodyIterator lastBody = Bodies.last(); 
  
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
          Collision* collideEvent = new Collision(AShape, BShape);

          bool push = true;
          for (unsigned i = 0; push == true && i < curCollisions.size(); i++)
          {
            if ((curCollisions[i]->firstObj == collideEvent->firstObj && curCollisions[i]->otherObj == collideEvent->otherObj))
            {
              push = false;
            }
          }
          if(push == true)
            curCollisions.push_back(collideEvent);

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
  //update the bodies
  for (unsigned i = 0; i < curCollisions.size(); i++)
  {
    bool started = true;
    for (unsigned j = 0; started == true && j < prevCollisions.size(); j++)
    {
      if (curCollisions[i]->firstObj == prevCollisions[j]->firstObj && curCollisions[i]->otherObj == prevCollisions[j]->otherObj)
      {
        started = false;
        if (((Body*)curCollisions[i]->firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
        {
          CollisionPersisted start(curCollisions[i]->otherObj);
          curCollisions[i]->firstObj->GetOwner()->SendMessages(&start);
        }
        if (((Body*)curCollisions[i]->otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
        {
          CollisionPersisted start(curCollisions[i]->firstObj);
          curCollisions[i]->otherObj->GetOwner()->SendMessages(&start);
        }
      }
    }
    if (started == true)
    {
      if (((Body*)curCollisions[i]->firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionStarted persist(curCollisions[i]->otherObj);
        curCollisions[i]->firstObj->GetOwner()->SendMessages(&persist);
      }
      if (((Body*)curCollisions[i]->otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionStarted persist(curCollisions[i]->firstObj);
        curCollisions[i]->otherObj->GetOwner()->SendMessages(&persist);
      }
    }
  }
  for (unsigned i = 0; i < prevCollisions.size(); i++)
  {
    bool ended = true;
    for (unsigned j = 0; ended == true && j < curCollisions.size(); j++)
    {
      if (curCollisions[j]->firstObj == prevCollisions[i]->firstObj && curCollisions[j]->otherObj == prevCollisions[i]->otherObj)
      {
        ended = false;
      }
    }
    if (ended == true)
    {
      if (((Body*)curCollisions[i]->firstObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionEnded end(curCollisions[i]->otherObj);
        curCollisions[i]->firstObj->GetOwner()->SendMessages(&end);
      }
      if (((Body*)curCollisions[i]->otherObj->GetOwner()->GetComponent(CT_Body))->IsStatic == false)
      {
        CollisionEnded end(curCollisions[i]->firstObj);
        curCollisions[i]->otherObj->GetOwner()->SendMessages(&end);
      }
    }
  }
  while (prevCollisions.size())
  {
    delete prevCollisions.back();
    prevCollisions.pop_back();
  }
  while (curCollisions.size())
  {
    prevCollisions.push_back(curCollisions.back());
    curCollisions.pop_back();
  }
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


}



void Physics::SendMessage(Message * m)
{

};



