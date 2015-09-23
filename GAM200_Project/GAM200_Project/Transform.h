#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "./physicsLib/vector2d.h"
#include "Composition.h"
namespace Framework
{
  class Transform : public GameComponent
  {
  public:
    Transform();
    Vector2D Position;
    float Rotation;
  };
}
#endif