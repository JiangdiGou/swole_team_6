#ifndef BODY_H
#define BODY_H

#include "math_utility.h"
//#include "our entity header file"
#include <vector> //for the vector of trigger callbacks
#include <utility> //pair
#include "../Composition.h"
//#include "PhysicsManager.h"
//#include "Trigger.h"
#include "Transform.h"
#include "../WindowsSystem.h"
#include "Collision.h"



class Body : public GameComponent
{
public:
	Body();
	~Body();

	void AddForce(Vec2D force);
	void Integrate(float dt);
	void SetPosition(Vec2D);
	void SetVelocity(Vec2D);
	void PublishResults();

	//Draw the object using the debug drawer
	void DebugDraw();

	virtual void Initialize();
	//virtual void Serialize(ISerializer& stream);

	Body * Next;
	Body * Prev;

	Vec2D Position;
	Vec2D PrevPosition;
	Vec2D Velocity;
	Vec2D Acceleration;
	float Mass;
	float InvMass;
	float Restitution;
	float Friction;
	float Damping;
	Vec2D AccumulatedForce;

	//Transform for this body
	Transform * tx;
	//Shape used for collision with this body
	Shape * BodyShape;
	//Static object are immovable fixed objects
	bool IsStatic;
	bool IsGhost;
	bool CheckDetectsCollision();
};





#endif 