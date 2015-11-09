#include "Collision.h"
//#include "Precompiled.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "RayLineBoxCollision.h"
////////////////////////////////////////////////////////////////////////////////
//Ray class implementation
Ray::Ray(float o_x, float o_y, float d_x, float d_y) : origin_x(o_x), origin_y(o_y), dir_x(d_x), dir_y(d_y) {}

//std::ostream& operator<<(std::ostream& os, Ray const& ray) {
//	os << " origin(" << ray.origin_x << "," << ray.origin_y << "), direction ( " << ray.dir_x << "," << ray.dir_y << ")";
//	return os;
//}

float const& Ray::Origin_x()    const { return origin_x; }
float const& Ray::Origin_y()    const { return origin_y; }
float const& Ray::Direction_x() const { return dir_x; }
float const& Ray::Direction_y() const { return dir_y; }

std::pair<bool, float>  Ray::IntersectSegment(float p1x, float p1y, float p2x, float p2y) const {
	float ox = origin_x;
	float oy = origin_y;
	float dx = dir_x;
	float dy = dir_y;

	//std::cout << "Segment " << p1x << "," << p1y << " - " << p2x << "," << p2y << " with ray " << ray << std::endl;

	//ray parametric:      XR = ox + dx*t, YR = oy + dy*t
	//segment parametric:  XI = p1x + (p2x-p1x)*s, YI = p1y + (p2y-p1y)*s
	//solve for t, make sure 0<s<1 (strict inequality means corner point 
	//does not reflect the ray)

	//solve system:
	//ox + dx*t = p1x + (p2x-p1x)*s
	//oy + dy*t = p1y + (p2y-p1y)*s
	//-----------------------------
	//dx*t = p1x + (p2x-p1x)*s - ox
	//dy*t = p1y + (p2y-p1y)*s - oy
	//-----------------------------
	//dy*dx*t = dy*( p1x + (p2x-p1x)*s - ox )
	//dx*dy*t = dx*( p1y + (p2y-p1y)*s - oy )
	//-----------------------------
	//dy*( p1x + (p2x-p1x)*s - ox ) = dx*( p1y + (p2y-p1y)*s - oy )
	//-----------------------------
	//dy*p1x + dy*(p2x-p1x)*s - dy*ox = dx*p1y + dx*(p2y-p1y)*s - dx*oy
	//-----------------------------
	//dy*(p2x-p1x)*s - dx*(p2y-p1y)*s = dx*p1y - dx*oy + dy*ox - dy*p1x
	//-----------------------------
	//[ dy*(p2x-p1x) - dx*(p2y-p1y) ]*s = dx*p1y - dx*oy + dy*ox - dy*p1x

	if (dy*(p2x - p1x) - dx*(p2y - p1y) == 0) { // parallel lines
		//std::cout << "parallel\n";
		return std::make_pair(false, -1);
	}

	float s = (dx*p1y - dx*oy + dy*ox - dy*p1x) / (dy*(p2x - p1x) - dx*(p2y - p1y));
	if (s < 0 || s> 1) {
		//std::cout << "c<=0 or c>=1\n";
		return std::make_pair(false, -1);
	}

	//to find t use any of the previous equations, for example 
	//ox + dx*t = p1x + (p2x-p1x)*s
	//t = [ p1x - ox + ( (p2x-p1x)*s ) ] / dx
	float t;
	if (dx == 0) { //vertical segment
		//use 
		//oy + dy*t = p1y + (p2y-p1y)*s 
		//t = [ p1y - oy  + (p2y-p1y)*s ] / dy
		//dx and dy cannot be both 0
		t = (p1y - oy + (p2y - p1y)*s) / dy;
	}
	else {
		t = (p1x - ox + ((p2x - p1x)*s)) / dx;
	}

	//only if t is positive
	//std::cout << "t = " << t << "\n";
	return t >= 0 ? std::make_pair(true, t) : std::make_pair(false, -1.0f);
}


////////////////////////////////////////////////////////////////////////////////
//BoundingCircle implementation
//BoundingCircle::BoundingCircle(float c_x, float c_y, float r) : center_x(c_x), center_y(c_y), radius(r) {}
//
//bool BoundingCircle::IntersectTest(Ray const& ray) const {
//	float ox = ray.Origin_x();
//	float oy = ray.Origin_y();
//	float dx = ray.Direction_x();
//	float dy = ray.Direction_y();
//	//to test - find distance from circle center to  the ray, 
//	//if <=r - there is intersection
//	//use ray equation (X-ox)*dy - (Y-oy)*dx = 0
//	//then distance is      [ (cx-ox)*dy - (cy-oy)*dx ] / sqrt( dx^2+dy^2 ) 
//	//to eliminate sqrt:    [ (cx-ox)*dy - (cy-oy)*dx ]^2 / ( dx^2+dy^2 ) < r^2
//	float temp = ((center_x - ox)*dy - (center_y - oy)*dx);
//	return ((temp*temp) / (dx*dx + dy*dy) <= radius*radius);
//}

//std::ostream & operator<< (std::ostream & os, BoundingCircle const& bs) {
//	os << "center (" << bs.center_x << "," << bs.center_y << "), radius " << bs.radius;
//	return os;
//}


////////////////////////////////////////////////////////////////////////////////
//Shape class implementation
CastShape::~CastShape() {}

////////////////////////////////////////////////////////////////////////////////
//Box class implementation
Box::Box(float c_x, float c_y, float s_x, float s_y) : center_x(c_x), center_y(c_y), side_x(s_x), side_y(s_y) {}

std::pair<bool, float> Box::Intersect(Ray const& ray) const {
	//for each side (segment) solve segment-ray intersection and find minimum
	/*
	// +--------------+/
	// |              +
	// |             /| may be 2 intersection points
	// |            / |
	// +-----------+--+
	//            / ray
	*/

	bool intersect = false;
	float t = std::numeric_limits<float>::max();
	std::pair<bool, float> t1 = ray.IntersectSegment(
		center_x - side_x / 2, center_y - side_y / 2,
		center_x + side_x / 2, center_y - side_y / 2);
	if (t1.first) { t = ((t1.second<t) ? t1.second : t); intersect = true; }
	std::pair<bool, float>  t2 = ray.IntersectSegment(
		center_x - side_x / 2, center_y - side_y / 2,
		center_x - side_x / 2, center_y + side_y / 2);
	if (t2.first) { t = ((t2.second<t) ? t2.second : t); intersect = true; }
	std::pair<bool, float>  t3 = ray.IntersectSegment(
		center_x + side_x / 2, center_y + side_y / 2,
		center_x - side_x / 2, center_y + side_y / 2);
	if (t3.first) { t = ((t3.second<t) ? t3.second : t); intersect = true; }
	std::pair<bool, float>  t4 = ray.IntersectSegment(
		center_x + side_x / 2, center_y + side_y / 2,
		center_x + side_x / 2, center_y - side_y / 2);
	if (t4.first) { t = ((t4.second<t) ? t4.second : t); intersect = true; }

	return std::make_pair(intersect, t);

}

////////////////////////////////////////////////////////////////////////////////
//Rhombus class implementation
//Rhombus::Rhombus(float c_x, float c_y, float dia_x, float dia_y) : center_x(c_x), center_y(c_y), diag_x(dia_x), diag_y(dia_y) {}
//
////BoundingCircle Rhombus::GetBoundingCircle() const {
////	return BoundingCircle(center_x, center_y, std::max(diag_x, diag_y) / 2);
////}
//
//std::pair<bool, float> Rhombus::Intersect(Ray const& ray) const {
//	//for each side (segment) solve segment-ray intersection and find minimum
//	/*           X
//	//          / \     may be 2 intersection points.
//	//     ----+---+---<--------ray
//	//        /     \
//	//       X       X
//	//        \     /
//	//         \   /
//	//          \ /
//	//           X
//	*/
//	bool intersect = false;
//	float t = std::numeric_limits<float>::max();
//	std::pair<bool, float> t1 = ray.IntersectSegment(
//		center_x - diag_x / 2, center_y,
//		center_x, center_y - diag_y / 2);
//	if (t1.first) { t = ((t1.second<t) ? t1.second : t); intersect = true; }
//	std::pair<bool, float>  t2 = ray.IntersectSegment(
//		center_x - diag_x / 2, center_y,
//		center_x, center_y + diag_y / 2);
//	if (t2.first) { t = ((t2.second<t) ? t2.second : t); intersect = true; }
//	std::pair<bool, float>  t3 = ray.IntersectSegment(
//		center_x + diag_x / 2, center_y,
//		center_x, center_y + diag_y / 2);
//	if (t3.first) { t = ((t3.second<t) ? t3.second : t); intersect = true; }
//	std::pair<bool, float>  t4 = ray.IntersectSegment(
//		center_x + diag_x / 2, center_y,
//		center_x, center_y - diag_y / 2);
//	if (t4.first) { t = ((t4.second<t) ? t4.second : t); intersect = true; }
//
//	return std::make_pair(intersect, t);
//
//}

//std::ostream & operator<< (std::ostream & os, Rhombus const& rhombus) {
//	os << "Rhombus( center (" << rhombus.center_x << "," << rhombus.center_y << "), diagonals ("
//		<< rhombus.diag_x << "," << rhombus.diag_y << ") )";
//	return os;
//}

//void Rhombus::Print() const {
//	std::cout << *this;
//}




bool line_rectangle_collide(Vec2D startBase, Vec2D endPoint, ShapeAAB* object)
{


	ShapeLine LineA;
	ShapeAAB * boxB;
	//LineA = (ShapeLine*)object->GetComponent(CT_ShapeLine);

	LineA.base = startBase;
	LineA.direction = endPoint - startBase;
	boxB = object;

	//ShapeAAB * Box = (ShapeAAB*)endDirection;

	GOC* bowner = boxB->GetOwner();
	Transform* boxTrans = bowner->has(Transform);
	//Transform* bTrans = r->GetOwner()->has(Transform);
	//at = aTrans->GetPositionXY();
	//bt = bTrans->GetPositionXY();
	////Check X
	//Vec2D positionDelta = at - bt;


    Vec2D n = Vec2D::rotate_vector_90(&LineA.direction);

	float dp1, dp2, dp3, dp4;

	//Vec2D c1 = boxB->origin;
	Vec2D c1 = Vec2D::subtract_vector(&boxTrans->GetPositionXY(), &(boxB->Extents));
	Vec2D c2 = Vec2D::add_vector(&c1, &(2*boxB->Extents));
	Vec2D c3 = { c2.x, c1.y };
	Vec2D c4 = { c1.x, c2.y };

	c1 = Vec2D::subtract_vector(&c1, &LineA.base);
	c2 = Vec2D::subtract_vector(&c2, &LineA.base);
	c3 = Vec2D::subtract_vector(&c3, &LineA.base);
	c4 = Vec2D::subtract_vector(&c4, &LineA.base);

	dp1 = Vec2D::DotProduct(n, c1);
	dp2 = Vec2D::DotProduct(n, c2);
	dp3 = Vec2D::DotProduct(n, c3);
	dp4 = Vec2D::DotProduct(n, c4);

	//return (dp1 * dp2 <= 0) || (dp2 * dp3 <= 0) || (dp3 * dp4 <= 0);
	if ((dp1 * dp2 <= 0) || (dp2 * dp3 <= 0) || (dp3 * dp4 <= 0))
	{

		//ManifoldSet * contact = c->GetNewContact();
		//contact->Bodies[0] = Line->body;
		//contact->Bodies[1] = Box->body;
		//contact->ContactNormal = positionDelta;//A to B
		//contact->Penetration = 0.0f;
		//contact->Restitution = DetermineRestitution(l->body, r->body);
		//contact->FrictionCof = DetermineFriction(l->body, r->body);
		if ((LineA.direction - startBase).Magnitude() / 2.5 > (boxTrans->GetPositionXY() - startBase ).Magnitude() * 2.7f)
		{
			printf("Slash Slash Slash !!!!\n");
			return true;
		}
		else
			return false;
	}
	else
		return false;


}

std::vector <const GameObjectComposition*> LoopAll(Vec2D start, Vec2D end)
{
	//if (start == Vec2D(0.0f, 0.0f) && end == Vec2D(0.0f, 0.0f))
		

	std::vector<const GameObjectComposition*> collidedObj;

	std::map<int, GameObjectComposition*>::iterator it = FACTORY->gameObjs.begin();
	int size = FACTORY->gameObjs.size();

	for (; it != FACTORY->gameObjs.end(); ++it)
	{
		std::cout << it->second->GetId() << std::endl;
		ShapeAAB* shape = (ShapeAAB*)it->second->GetComponent(CT_ShapeAAB);
		if (shape != NULL)
			if (line_rectangle_collide(start, end, shape))
			{
				std::cout << it->second->GetName() << std::endl;
				std::cout << "Im in loop" << std::endl;
				//collidedObj.push_back(it->second);
			}
	}
	/*for (int i = 0; i < FACTORY->gameObjs.size(); i++)
	{
		if (FACTORY->gameObjs[i] != NULL){
			//obj = FACTORY->gameObjs.at(i);
			if (line_rectangle_collide(start, end, FACTORY->gameObjs.at(i)))
			{
			std::cout << "Im in loop" << std::endl;
			collidedObj.push_back(FACTORY->gameObjs[i]);
			}
		}
	}*/

	 //std::vector<const GameObjectComposition*> daiodj = std::vector<const GameObjectComposition*>();
	//return collidedObj;
	 return collidedObj;
	//return collidingobj;
}