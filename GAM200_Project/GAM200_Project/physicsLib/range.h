#pragma once

#include "boolean.h"

typedef struct
{
	float minimum;
	float maximum;
} Range;

bool overlapping_ranges(const Range* a, const Range* b)
{
    return b->minimum <= a->maximum && a->minimum <= b->maximum;
}

Range range_hull(const Range* a, const Range* b)
{
	Range hull;
	hull.minimum = a->minimum < b->minimum ? a->minimum : b->minimum;
	hull.maximum = a->maximum > b->maximum ? a->maximum : b->maximum;
	return hull;
}

Range sort_range(const Range* r)
{
	Range sorted = *r;
    if(r->minimum > r->maximum)
	{
		sorted.minimum = r->maximum;
		sorted.maximum = r->minimum;
    }
	return sorted;
}