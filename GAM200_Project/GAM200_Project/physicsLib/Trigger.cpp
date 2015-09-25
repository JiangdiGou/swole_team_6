//#include "Precompiled.h"
#include "../Composition.h"
#include "Trigger.h"

CollisionDelegate::CollisionDelegate(GameObjectComposition *parent) : parent_(parent)
{
}

void CollisionDelegate::InitializeCollisionCallback()
{
	reinterpret_cast<RigidBody*>(parent->GetComponent(CT_Body))->AddTriggerCallback(this);
}
