#ifndef TRIGGER_H
#define TRIGGER_H

//#include "Composition.h" <-- We don't need it for just pointers

//Have a class inherit CollisionDelegate to allow one of its functions to override Callback.
//When Initialize is called (it must be called by the inheritor, preferably in Initialize),
//It adds its information to the list of delegates in its object's Rigidbody.
//When the object collides with another, all collision delegates will be called.

//Forward declaration
class GameObjectComposition; //<-- This will suffice

class CollisionDelegate
{
public:
	CollisionDelegate(GameObjectComposition *parent);
	void InitializeCollisionCallback();
	//The callback function
	virtual void OnCollision(GameObjectComposition *object) = 0;
	CollisionDelegate();

private:
	GameObjectComposition *const parent_;
	//These should never happen:
	//CollisionDelegate();
	CollisionDelegate(CollisionDelegate &rhs);
};

#endif