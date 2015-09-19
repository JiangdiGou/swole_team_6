#pragma once

#include "vector2d.h"
#include "shapes.h"
//#include "math_utility.h"

Rectangle enlarge_rectangle_point(const Rectangle* r, const Vector2D* p)
{
    Rectangle enlarged;
    enlarged.origin.x = minimum(r->origin.x, p->x);
    enlarged.origin.y = minimum(r->origin.y, p->y);
    enlarged.size.x = maximum(r->origin.x + r->size.x, p->x);
    enlarged.size.y = maximum(r->origin.y + r->size.y, p->y);
	enlarged.size = subtract_vector(&enlarged.size, &enlarged.origin);
    return enlarged;
}

Rectangle enlarge_rectangle_rectangle(const Rectangle* r, const Rectangle* extender)
{
	const Vector2D maxCorner = add_vector(&extender->origin, &extender->size);
	Rectangle enlarged = enlarge_rectangle_point(r, &maxCorner);
    return enlarge_rectangle_point(&enlarged, &extender->origin);
}

Rectangle oriented_rectangle_rectangle_hull(const OrientedRectangle* r)
{
	Rectangle h = {{r->center.x, r->center.y}, {0, 0}};
	
	int nr;
	Vector2D corner;
	for(nr = 0; nr < 4; ++nr)
	{
		corner = oriented_rectangle_corner(r, nr);
		h = enlarge_rectangle_point(&h, &corner);
	}
    return h;
}

Rectangle rectangles_rectangle_hull(const Rectangle* rectangles, int count)
{
	int i;
	Rectangle h = {{0, 0}, {0, 0}};
	if(0 == count)
		return h;

    h = rectangles[0];
    for(i = 1; i < count; ++i)
        h = enlarge_rectangle_rectangle(&h, &rectangles[i]);

    return h;
}

Circle oriented_rectangle_circle_hull(const OrientedRectangle* r)
{
	Circle h;
	h.center = r->center;
	h.radius = vector_length(&r->halfExtend);
	return h;
}

Rectangle circles_rectangle_hull(const Circle* circles, int count)
{
	int i;
	Vector2D halfExtend, minP, maxP;
	Rectangle h = {{0, 0}, {0, 0}};
	if(0 == count)
		return h;

	h.origin = circles[0].center;
	for(i = 0; i < count; ++i)
	{
		halfExtend.x = halfExtend.y = circles[i].radius;
		minP = subtract_vector(&circles[i].center, &halfExtend);
		maxP = add_vector(&circles[i].center, &halfExtend);
		h = enlarge_rectangle_point(&h, &minP);
		h = enlarge_rectangle_point(&h, &maxP);
	}
	return h;
}

Circle circles_circle_hull(const Circle* circles, int count)
{
	int i;
	Circle h = {{0, 0}, 0};
	const Rectangle rh = circles_rectangle_hull(circles, count);
	h.center = rectangle_center(&rh);
	
	for(i = 0; i < count; ++i)
	{
        const Vector2D d = subtract_vector(&circles[i].center, &h.center);
		h.radius = maximum(vector_length(&d) + circles[i].radius, h.radius);
	}
	return h;
}