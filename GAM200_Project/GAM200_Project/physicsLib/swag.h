#pragma once

#include "math_utility.h"
#include "boolean.h"
#include <math.h>

typedef struct
{
    float x;
    float y;
} Vector2D;
Vector2D createVector2D(float x, float y)
{
  Vector2D newVec = { x, y };
  return newVec;
}
Vector2D add_vector(const Vector2D* a, const Vector2D* b)
{
	const Vector2D r = {a->x + b->x, a->y + b->y};
    return r;
}

Vector2D subtract_vector(const Vector2D* a, const Vector2D* b)
{
	const Vector2D r = {a->x - b->x, a->y - b->y};
    return r;
}

Vector2D negate_vector(const Vector2D* v)
{
	const Vector2D n = {-v->x, -v->y};
    return n;
}

Vector2D multiply_vector(const Vector2D* v, float s)
{
    const Vector2D r = {v->x * s, v->y * s};
	return r;
}

Vector2D divide_vector(const Vector2D* v, float d)
{
    const Vector2D r = {v->x / d, v->y / d};
	return r;
}

float dot_product(const Vector2D* a, const Vector2D* b)
{
	return a->x * b->x + a->y * b->y;
}

float vector_length(const Vector2D* v)
{
	return sqrtf(dot_product(v, v));
}

Vector2D rotate_vector(const Vector2D* v, float degrees)
{
    const float radian = degrees_to_radian(degrees);
    const float sine = sinf(radian);
    const float cosine = cosf(radian);

	const Vector2D r = {v->x * cosine - v->y * sine, v->x * sine + v->y * cosine};
    return r;
}

Vector2D rotate_vector_90(const Vector2D* v)
{
	const Vector2D r = {-(v->y), v->x};
    return r;
}

Vector2D rotate_vector_180(const Vector2D* v)
{
	return negate_vector(v);
}

Vector2D rotate_vector_270(const Vector2D* v)
{
	const Vector2D r = {v->y, -(v->x)};
    return r;
}

Vector2D unit_vector(const Vector2D* v)
{
	const float length = vector_length(v);
	if(length != 0)
		return divide_vector(v, length);
	return *v;
}

float enclosed_angle(const Vector2D* a, const Vector2D* b)
{
    const Vector2D ua = unit_vector(a);
    const Vector2D ub = unit_vector(b);
    const float dp = dot_product(&ua, &ub);
    return radian_to_degrees(acosf(dp));
}

Vector2D project_vector(const Vector2D* project, const Vector2D* onto)
{
    const float d = dot_product(onto, onto);
	if(0 != d)
        return multiply_vector(onto, dot_product(project, onto) / d);
    return *onto;
}

