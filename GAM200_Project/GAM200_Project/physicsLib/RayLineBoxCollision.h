#ifndef RAYLINEBOXCOLLISION_H
#define RAYLINEBOXCOLLISION_H

//#include "primitive.h"
//#include "Resolution.h"
//#include "Body.h"
#include "math_utility.h"
#include "../Composition.h"
#include "Collision.h"
#include "../gameComponents/objFactory.h"
#include "../mouseVector.h"
//ShapeAAB * Mybox;



std::vector <GameObjectComposition*> LoopAll(Vec2D start, Vec2D end);

bool line_rectangle_collide(Vec2D startBase, Vec2D endDirection);

#endif