#pragma once
#include "primitive.h"
#include "Resolution.h"
#include "Body.h"
#include "CollisionCheck.h"
#include "math_utility.h"

struct Manifold;
class RigidBody;

typedef void(*CollisionTest)(Primitive *a, Primitive *b, Manifold *data);
extern CollisionTest CollisionRegistry[Primitive::pCount][Primitive::pCount];

void CircleAndCircle(Primitive *a, Primitive *b, Manifold *data);
void AABBAndAABB(Primitive *a, Primitive *b, Manifold *data);
void AABBAndCircle(Primitive *a, Primitive *b, Manifold *data);
void CircleAndAABB(Primitive *b, Primitive *a, Manifold *data);
float Clamp(float, float, float);