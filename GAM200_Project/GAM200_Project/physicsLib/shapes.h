#pragma once

#include "vector2d.h"

typedef struct
{
	Vector2D base;
	Vector2D direction;
} Line;

typedef struct
{
	Vector2D point1;
	Vector2D point2;
} Segment;

typedef struct
{
    Vector2D center;
    float radius;
} Circle;

typedef struct
{
    Vector2D origin;
    Vector2D size;
} Rectangle;

typedef struct
{
    Vector2D center;
    Vector2D halfExtend;
    float rotation;
} OrientedRectangle;

Vector2D rectangle_center(const Rectangle* r)
{
	Vector2D center;
	center.x = r->origin.x + r->size.x / 2;
	center.y = r->origin.y + r->size.y / 2;
	return center;
}
