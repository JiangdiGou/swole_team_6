#pragma once
#include "primitive.h"
#include "Resolution.h"
#include "CollisionCheck.h"
#include "math_utility.h"

struct Manifold;
class RigidBody;

typedef void(*CollisionTest)(RigidBody *a, RigidBody *b, Manifold *data);
extern CollisionTest CollisionRegistry[Primitive::pCount][Primitive::pCount];

void CircleAndCircle(RigidBody *a, RigidBody *b, Manifold *data);
void AABBAndAABB(RigidBody *a, RigidBody *b, Manifold *data);
void AABBAndCircle(RigidBody *a, RigidBody *b, Manifold *data);
void CircleAndAABB(RigidBody *b, RigidBody *a, Manifold *data);
float Clamp(float, float, float);