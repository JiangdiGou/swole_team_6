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
//class Primitive;
//class Circle;
//class AABB;

//sample engine

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


};



//RigidBody GameComponent
//class RigidBody : public GameComponent
//	{
//	public:
//
//		// Will make these variables private later
//		friend class Primitive;
//		friend class Circle;
//		friend class AABB;
//		//WE NEED A TRANSFORM COMPONET
//    Transform *pTrans;
//		//Vector2 position;
//		Vector2 acceleration;
//		Primitive *bodyShape;
//		      // Holds the linear velocity of the rigid body
//		Vector2 forceAccum;     // Accumlated force
//		float mass;             // Holds the mass of the rigid body
//		float invMass;          // Holds the inverted mass
//		float rotation;         // Holds the rotation
//		float restitution;      // Holds the restitution
//		float angularVelocity;
//		float orientation;
//		float inertia;
//		float invInertia;
//
//
//		          // True if object is static
//		// Set where rigidbody doesn't have a resolution
//		bool isGhost;
//		bool useGravity;         // Set gravity on or off
//		bool isKinematic;        // Something to be added 
//
//
//		// WE NEED ENTITY FILE AND PRIMITIVE
//		RigidBody(/*Primitive *shape*/);
//		//RigidBody();
//		~RigidBody();
//
//		void Initialize() override;
//		void Update(float dt) override;
//    void Release() override;
//    void SendMessages(Message * message) override;
//
//		void set(float mass);
//		/*void 
//		(const Vector2 &position);
//		void setPosition(const float x, const float y);
//		Vector2 getPosition() const;*/
//
//		// Set the acceleration
//		void setAcceleration(const Vector2 &acc);
//		void setAcceleration(const float x, const float y);
//		Vector2 getAcceleration() const;
//
//		void setVelocity(const Vector2 &velocity);
//		void setVelocity(const float x, const float y);
//		Vector2 getVelocity() const;
//
//		void setMass(const float mass);
//		float getMass() const;
//		float getInvMass() const;
//
//		void setRotation(const float rotation);
//		float getRotation() const;
//
//		void AddForce(const Vector2 &force);
//		void SetStatic(void);
//    void ApplyImpulse(const Vector2& impulse, const Vec2D& contactVec);
//		void SetOrientation(float radians);
//
//		bool IsStatic();
//		bool isStatic;
//		bool CheckDetectsCollision();
//		void SetDensity(float density);  //Sets the mass based on the attached colliders assuming a constant density.
//
//
//		//Called in PhysicsManager when two objects collide
//		void Trigger(GameObjectComposition *collObj);
//    void AddTriggerCallback(CollisionDelegate *del);
//		//Vector of pairs of collision delegate methods and the objects they're in.
//		//(Is all of this necessary? Could you just have one function since it's all the same name?)
//		std::vector <CollisionDelegate *> triggerCallbacks;
//	//private:
//		//PhysicsManager *physics;
//
//	private:
//		
//		Vector2 velocity;
//	};
//}

#endif 