#ifndef TRIGGER_H
#define TRIGGER_H

//Forward declaration
class GameObjectComposition; 

class CollisionDelegate
{
public:
	CollisionDelegate(GameObjectComposition *parent);
	void InitializeCollisionCallback();
	//The callback function
	virtual void OnCollision(GameObjectComposition *object) = 0;


private:
	GameObjectComposition *const parent_;
	CollisionDelegate();
	CollisionDelegate(CollisionDelegate &rhs);
};

#endif