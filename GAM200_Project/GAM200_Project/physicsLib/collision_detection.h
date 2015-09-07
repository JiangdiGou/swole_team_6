#pragma once

#include "boolean.h"
#include "shapes.h"
#include "vector2d.h"
#include "collision_detection_utility.h"
#include "bounding_shapes.h"

Bool circles_collide(const Circle* a, const Circle* b)
{
    const float radiusSum = a->radius + b->radius;
	const Vector2D distance = subtract_vector(&(a->center), &(b->center));
    return dot_product(&distance, &distance) <= radiusSum * radiusSum;
}

Bool circle_point_collide(const Circle* c, const Vector2D* p)
{
	const Vector2D distance = subtract_vector(&(c->center), p);
	return dot_product(&distance, &distance) <= c->radius * c->radius;
}

Bool circle_line_collide(const Circle* c, const Line* l)
{
    const Vector2D lc = subtract_vector(&c->center, &l->base);
	Vector2D p = project_vector(&lc, &l->direction);
	p = add_vector(&l->base, &p);
    return circle_point_collide(c, &p);
}

Bool circle_rectangle_collide(const Circle* c, const Rectangle* r)
{
    const Vector2D clamped = clamp_on_rectangle(&c->center, r);
    return circle_point_collide(c, &clamped);
}

Bool circle_segment_collide(const Circle* c, const Segment* s)
{
	if(circle_point_collide(c, &s->point1) || circle_point_collide(c, &s->point2))
		return yes;

	{
		const Vector2D d = subtract_vector(&s->point2, &s->point1);
		const Vector2D lc = subtract_vector(&c->center, &s->point1);
		const Vector2D p = project_vector(&lc, &d);
		const Vector2D nearest = add_vector(&s->point1, &p);
		return circle_point_collide(c, &nearest) && dot_product(&p, &p) <= dot_product(&d, &d) && 0 <= dot_product(&p, &d);
	}
}

Bool circle_oriented_rectangle_collide(const Circle* c, const OrientedRectangle* r)
{
	const Rectangle lr = {{0, 0}, {r->halfExtend.x * 2, r->halfExtend.y * 2}};

	Circle lc = {{0, 0}, c->radius};
    lc.center = subtract_vector(&c->center, &r->center);
	lc.center = rotate_vector(&lc.center, -r->rotation);
	lc.center = add_vector(&lc.center, &r->halfExtend);

	return circle_rectangle_collide(&lc, &lr);
}

Bool rectangles_collide(const Rectangle* a, const Rectangle* b)
{
    return
		overlapping(a->origin.x, a->origin.x + a->size.x, b->origin.x, b->origin.x + b->size.x) &&
		overlapping(a->origin.y, a->origin.y + a->size.y, b->origin.y, b->origin.y + b->size.y);
}

Bool points_collide(const Vector2D* a, const Vector2D* b)
{
	return equal_floats(a->x, b->x) && equal_floats(a->y, b->y);
}

Bool line_point_collide(const Line* l, const Vector2D* p)
{
    const Vector2D lp = subtract_vector(p, &l->base);
	return (lp.x == 0 && lp.y == 0) || parallel_vectors(&lp, &l->direction);
}

Bool lines_collide(const Line* a, const Line* b)
{
	return !parallel_vectors(&a->direction, &b->direction) || line_point_collide(a, &b->base);
}

Bool line_segment_collide(const Line* l, const Segment* s)
{
	return !on_one_side(l, s);
}

Bool point_segment_collide(const Vector2D* p, const Segment* s)
{
    const Vector2D d = subtract_vector(&s->point2, &s->point1);
    const Vector2D lp = subtract_vector(p, &s->point1);
    const Vector2D pr = project_vector(&lp, &d);
    return points_collide(&lp, &pr) && dot_product(&pr, &pr) <= dot_product(&d, &d) && 0 <= dot_product(&pr, &d);
}

Bool segments_collide(const Segment* a, const Segment* b)
{
	Line axisA, axisB;
	axisA.base = a->point1;
	axisA.direction = subtract_vector(&a->point2, &a->point1);
	if(0 == axisA.direction.x && 0 == axisA.direction.y)
		return point_segment_collide(&a->point1, b);
	else if(on_one_side(&axisA, b))
		return no;

	axisB.base = b->point1;
	axisB.direction = subtract_vector(&b->point2, &b->point1);
	if(0 == axisB.direction.x && 0 == axisB.direction.y)
		return point_segment_collide(&b->point1, a);
	else if(on_one_side(&axisB, a))
		return no;

	if(parallel_vectors(&axisA.direction, &axisB.direction))
	{
		const Vector2D d = unit_vector(&axisA.direction);
		const Range rangeA = project_segment(a, &d, yes);
		const Range rangeB = project_segment(b, &d, yes);
		return overlapping_ranges(&rangeA, &rangeB);
	}
	else
		return yes;
}

Bool line_rectangle_collide(const Line* l, const Rectangle* r)
{
	const Vector2D n = rotate_vector_90(&l->direction);

	float dp1, dp2, dp3, dp4;

    Vector2D c1 = r->origin;
    Vector2D c2 = add_vector(&c1, &r->size);
	Vector2D c3 = {c2.x, c1.y};
	Vector2D c4 = {c1.x, c2.y};

    c1 = subtract_vector(&c1, &l->base);
    c2 = subtract_vector(&c2, &l->base);
    c3 = subtract_vector(&c3, &l->base);
    c4 = subtract_vector(&c4, &l->base);

    dp1 = dot_product(&n, &c1);
    dp2 = dot_product(&n, &c2);
    dp3 = dot_product(&n, &c3);
    dp4 = dot_product(&n, &c4);

	return (dp1 * dp2 <= 0) || (dp2 * dp3 <= 0) || (dp3 * dp4 <= 0);
}

Bool line_oriented_rectangle_collide(const Line* l, const OrientedRectangle* r)
{
	const Rectangle lr = {{0, 0}, {r->halfExtend.x * 2, r->halfExtend.y * 2}};

	Line ll;
	ll.base = subtract_vector(&l->base, &r->center);
	ll.base = rotate_vector(&ll.base, -r->rotation);
	ll.base = add_vector(&ll.base, &r->halfExtend);
	ll.direction = rotate_vector(&l->direction, -r->rotation);

    return line_rectangle_collide(&ll, &lr);
}

Bool oriented_rectangles_collide(const OrientedRectangle* a, const OrientedRectangle* b)
{
	Segment edge = oriented_rectangle_edge(a, 0);
	if(separating_axis_for_oriented_rectangle(&edge, b))
		return no;

	edge = oriented_rectangle_edge(a, 1);
	if(separating_axis_for_oriented_rectangle(&edge, b))
		return no;

	edge = oriented_rectangle_edge(b, 0);
	if(separating_axis_for_oriented_rectangle(&edge, a))
		return no;

	edge = oriented_rectangle_edge(b, 1);
	return !separating_axis_for_oriented_rectangle(&edge, a);
}

Bool point_rectangle_collide(const Vector2D* p, const Rectangle* r)
{
    const float left = r->origin.x;
    const float right = left + r->size.x;
    const float bottom = r->origin.y;
    const float top = bottom + r->size.y;
    return left <= p->x && bottom <= p->y && p->x <= right && p->y <= top;
}

Bool oriented_rectangle_point_collide(const OrientedRectangle* r, const Vector2D* p)
{
	const Rectangle lr = {{0, 0}, {r->halfExtend.x * 2, r->halfExtend.y * 2}};
    Vector2D lp = subtract_vector(p, &r->center);
	lp = rotate_vector(&lp, -r->rotation);
	lp = add_vector(&lp, &r->halfExtend);

    return point_rectangle_collide(&lp, &lr);
}

Bool oriented_rectangle_rectangle_collide(const OrientedRectangle* or, const Rectangle* aar)
{
	Segment edge;
	const Rectangle orHull = oriented_rectangle_rectangle_hull(or);
	if(!rectangles_collide(&orHull, aar))
		return no;

	edge = oriented_rectangle_edge(or, 0);
	if(separating_axis_for_rectangle(&edge, aar))
		return no;

	edge = oriented_rectangle_edge(or, 1);
	return !separating_axis_for_rectangle(&edge, aar);
}

Bool rectangle_segment_collide(const Rectangle* r, const Segment* s)
{
	Line sLine;
	Range rRange = {r->origin.x, r->origin.x + r->size.x};
	Range sRange = {s->point1.x, s->point2.x};
	sRange = sort_range(&sRange);
	if(!overlapping_ranges(&rRange, &sRange))
		return no;

	rRange.minimum = r->origin.y;
	rRange.maximum = r->origin.y + r->size.y;
	sRange.minimum = s->point1.y;
	sRange.maximum = s->point2.y;
	sRange = sort_range(&sRange);
	if(!overlapping_ranges(&rRange, &sRange))
		return no;

	sLine.base = s->point1;
	sLine.direction = subtract_vector(&s->point2, &s->point1);
    return line_rectangle_collide(&sLine, r);
}

Bool oriented_rectangle_segment_collide(const OrientedRectangle* r, const Segment* s)
{
	const Rectangle lr = {{0, 0}, {r->halfExtend.x * 2, r->halfExtend.y * 2}};

	Segment ls;
    ls.point1 = subtract_vector(&s->point1, &r->center);
    ls.point1 = rotate_vector(&ls.point1, -r->rotation);
    ls.point1 = add_vector(&ls.point1, &r->halfExtend);
    ls.point2 = subtract_vector(&s->point2, &r->center);
    ls.point2 = rotate_vector(&ls.point2, -r->rotation);
    ls.point2 = add_vector(&ls.point2, &r->halfExtend);

    return rectangle_segment_collide(&lr, &ls);
}
