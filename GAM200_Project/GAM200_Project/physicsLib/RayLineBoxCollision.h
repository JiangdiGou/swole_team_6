#ifndef RAYLINEBOXCOLLISION_H
#define RAYLINEBOXCOLLISION_H

//#include "primitive.h"
//#include "Resolution.h"
//#include "Body.h"
#include "math_utility.h"
#include "../Composition.h"
#include "Collision.h"

class Ray {
private:
	float  origin_x;
	float  origin_y;
	float  dir_x;
	float  dir_y;
public:
	Ray(float o_x, float o_y, float d_x, float d_y);
	float const& Origin_x() const;
	float const& Origin_y() const;
	float const& Direction_x() const;
	float const& Direction_y() const;
	std::pair<bool, float> IntersectSegment(float p1_x, float p1_y, float p2_x, float p2_y) const;
	friend std::ostream & operator<< (std::ostream & os, Ray const& ray);
};

class BoundingCircle {
private:
	float  center_x;
	float  center_y;
	float  radius;
public:
	//BoundingCircle(float c_x, float c_y, float r);
	bool IntersectTest(Ray const& ray) const; //yes/no only
	/*friend std::ostream & operator<< (std::ostream & os, BoundingCircle const& bs);*/
};

//base shape class - abstract
class CastShape {
public:
	/*virtual BoundingCircle GetBoundingCircle() const = 0;*/
	virtual std::pair<bool, float> Intersect(Ray const& ray) const = 0;
	virtual void Print() const = 0;
	virtual ~CastShape();
};

class Box : public CastShape {
private:
	float center_x;
	float center_y;
	float side_x;
	float side_y;
public:
	Box(float c_x, float c_y, float s_x, float s_y);
	// compiler generated copy, assignment, destructor are OK
	/*BoundingCircle GetBoundingCircle() const;*/
	std::pair<bool, float> Intersect(Ray const& ray) const;
	/*void Print() const;
	friend std::ostream & operator<< (std::ostream & os, Box const& box);*/
};

class Rhombus : public CastShape {
private:
	float center_x;
	float center_y;
	float diag_x;
	float diag_y;
public:
	Rhombus(float c_x, float c_y, float dia_x, float dia_y);
	// compiler generated copy, assignment, destructor are OK
	/*BoundingCircle GetBoundingCircle() const;*/
	std::pair<bool, float> Intersect(Ray const& ray) const;
	/*void Print() const;
	friend std::ostream & operator<< (std::ostream & os, Rhombus const& rhombus);*/
};
bool line_rectangle_collide(Vec2D startBase, Vec2D endDirection);

#endif