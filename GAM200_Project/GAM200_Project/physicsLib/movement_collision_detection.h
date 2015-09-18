#pragma once

#include "collision_detection.h"
#include "bounding_shapes.h"
#include "shapes.h"
#include "vector2d.h"
//#include "math_utility.h"

bool moving_circle_circle_collide(const Circle* a, const Vector2D* moveA, const Circle* b)
{
	const Circle bAbsorbedA = { { b->center.x, b->center.y }, b->radius + a->radius };

	Segment travelA;
	travelA.point1 = a->center;
	travelA.point2 = add_vector(&a->center, moveA);

	return circle_segment_collide(&bAbsorbedA, &travelA);
}

bool moving_rectangle_rectangle_collide(const Rectangle* a, const Vector2D* moveA, const Rectangle* b)
{
	Rectangle envelope = *a;
	envelope.origin = add_vector(&envelope.origin, moveA);
	envelope = enlarge_rectangle_rectangle(&envelope, a);

	if (rectangles_collide(&envelope, b))
	{
		const float epsilon = 1.0f / 32.0f;/* improves case a->size is (close to) zero */
		const float minimumMoveDistance = maximum(minimum(a->size.x, a->size.y) / 4, epsilon);
		const Vector2D halfMoveA = divide_vector(moveA, 2);
		if (vector_length(moveA) < minimumMoveDistance)
			return yes;

		envelope.origin = add_vector(&a->origin, &halfMoveA);
		envelope.size = a->size;
		return
			moving_rectangle_rectangle_collide(a, &halfMoveA, b) ||
			moving_rectangle_rectangle_collide(&envelope, &halfMoveA, b);
	}
	else
		return no;
}

bool moving_circle_rectangle_collide(const Circle* a, const Vector2D* moveA, const Rectangle* b)
{
	Circle envelope = *a;
	const Vector2D halfMoveA = divide_vector(moveA, 2);
	const float moveDistance = vector_length(moveA);
	envelope.center = add_vector(&a->center, &halfMoveA);
	envelope.radius = a->radius + moveDistance / 2;

	if (circle_rectangle_collide(&envelope, b))
	{
		const float epsilon = 1.0f / 32.0f;/* improves case a->radius is (close to) zero */
		const float minimumMoveDistance = maximum(a->radius / 4, epsilon);
		if (moveDistance < minimumMoveDistance)
			return yes;

		envelope.radius = a->radius;
		return
			moving_circle_rectangle_collide(a, &halfMoveA, b) ||
			moving_circle_rectangle_collide(&envelope, &halfMoveA, b);
	}
	else
		return no;
}

bool moving_rectangle_circle_collide(const Rectangle* a, const Vector2D* moveA, const Circle* b)
{
	const Vector2D moveB = negate_vector(moveA);
	return moving_circle_rectangle_collide(b, &moveB, a);
}