#pragma once

#include "boolean.h"
#include "math_utility.h"
#include "vector2d.h"
#include "range.h"

bool overlapping(float minA, float maxA, float minB, float maxB)
{
    return minB <= maxA && minA <= maxB;
}

Range project_segment(const Segment* s, const Vector2D* onto, Bool ontoIsUnit)
{
	const Vector2D ontoUnit = ontoIsUnit ? *onto : unit_vector(onto);

    Range r;
	r.minimum = dot_product(&ontoUnit, &s->point1);
	r.maximum = dot_product(&ontoUnit, &s->point2);
	r = sort_range(&r);
    return r;
}

bool on_one_side(const Line* axis, const Segment* s)
{
	const Vector2D d1 = subtract_vector(&axis->base, &s->point1);
	const Vector2D d2 = subtract_vector(&axis->base, &s->point2);
	const Vector2D n = rotate_vector_90(&axis->direction);
	return dot_product(&n, &d1) * dot_product(&n, &d2) > 0;
}

float clamp_on_range(float x, float min, float max)
{
	return x < min ? min : (max < x ? max : x);
}

Vector2D clamp_on_rectangle(const Vector2D* p, const Rectangle* r)
{
	Vector2D clamp;
	clamp.x = clamp_on_range(p->x, r->origin.x, r->origin.x + r->size.x);
	clamp.y = clamp_on_range(p->y, r->origin.y, r->origin.y + r->size.y);
	return clamp;
}

bool parallel_vectors(const Vector2D* a, const Vector2D* b)
{
	const Vector2D na = rotate_vector_90(a);
	return !(0 == a->x && 0 == a->y) && !(0 == b->x && 0 == b->y) && equal_floats(0, dot_product(&na, b));
}

bool equal_vectors(const Vector2D* a, const Vector2D* b)
{
	return equal_floats(a->x, b->x) && equal_floats(a->y, b->y);
}

Vector2D rectangle_corner(const Rectangle* r, int nr)
{
	Vector2D corner = r->origin;
	switch(nr % 4)
	{
	case 0:
		corner.x += r->size.x;
		break;
	case 1:
		corner = add_vector(&corner, &r->size);
		break;
	case 2:
		corner.y += r->size.y;
		break;
	default:
		/* corner = r->origin */
		break;
	}
	return corner;
}

Vector2D oriented_rectangle_corner(const OrientedRectangle* r, int nr)
{
    Vector2D c = r->halfExtend;
    switch(nr % 4) {
        case 0:
            c.x = -c.x;
            break;
        case 1:
			/* c = r->halfExtend */
            break;
        case 2:
            c.y = -c.y;
            break;
        default:
            c = negate_vector(&c);
            break;
    }

	c = rotate_vector(&c, r->rotation);
    return add_vector(&c, &r->center);
}

Segment oriented_rectangle_edge(const OrientedRectangle* r, int nr)
{
	Segment edge;
    Vector2D a = r->halfExtend;
    Vector2D b = r->halfExtend;

    switch(nr % 4) {
        case 0:/* top edge */
            a.x = -a.x;
            break;
        case 1:/* right edge */
            b.y = -b.y;
            break;
        case 2:/* bottom edge */
            a.y = -a.y;
            b = negate_vector(&b);
            break;
        default:/* left edge */
            a = negate_vector(&a);
            b.x = -b.x;
            break;
    }

	a = rotate_vector(&a, r->rotation);
    a = add_vector(&a, &r->center);

	b = rotate_vector(&b, r->rotation);
    b = add_vector(&b, &r->center);

	edge.point1 = a;
	edge.point2 = b;
	return edge;
}

bool separating_axis_for_oriented_rectangle(const Segment* axis, const OrientedRectangle* r)
{
	Range axisRange, r0Range, r2Range, rProjection;
	Segment rEdge0 = oriented_rectangle_edge(r, 0);
	Segment rEdge2 = oriented_rectangle_edge(r, 2);
	Vector2D n = subtract_vector(&axis->point1, &axis->point2);

	n = unit_vector(&n);
    axisRange = project_segment(axis, &n, yes);
    r0Range = project_segment(&rEdge0, &n, yes);
    r2Range = project_segment(&rEdge2, &n, yes);
    rProjection = range_hull(&r0Range, &r2Range);

    return !overlapping_ranges(&axisRange, &rProjection);
}

bool separating_axis_for_rectangle(const Segment* axis, const Rectangle* r)
{
	Segment rEdgeA, rEdgeB;
	Range axisRange, rEdgeARange, rEdgeBRange, rProjection;
	Vector2D n = subtract_vector(&axis->point1, &axis->point2);

	n = unit_vector(&n);
	rEdgeA.point1 = rectangle_corner(r, 0);
	rEdgeA.point2 = rectangle_corner(r, 1);
	rEdgeB.point1 = rectangle_corner(r, 2);
	rEdgeB.point2 = rectangle_corner(r, 3);
	rEdgeARange = project_segment(&rEdgeA, &n, yes);
	rEdgeBRange = project_segment(&rEdgeB, &n, yes);
	rProjection = range_hull(&rEdgeARange, &rEdgeBRange);

    axisRange = project_segment(axis, &n, yes);

    return !overlapping_ranges(&axisRange, &rProjection);
}
