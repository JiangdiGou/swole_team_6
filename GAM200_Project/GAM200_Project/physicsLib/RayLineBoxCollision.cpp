

#include "Collision.h"
//#include "Precompiled.h"
#include "PhysicsManager.h"
#include "Transform.h"
#include "RayLineBoxCollision.h"
////////////////////////////////////////////////////////////////////////////////
//Ray class implementation




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
  Vec2D c2 = Vec2D::add_vector(&c1, &(2 * boxB->Extents));
  Vec2D c3 = { c2.x, c1.y };
  Vec2D c4 = { c1.x, c2.y };
  if (startBase.x < c2.x && startBase.x > c1.x && startBase.y < c2.y && startBase.y > c1.y)
  {
    //printf("slash");
    return true;
  }
  if (endPoint.x < c2.x && endPoint.x > c1.x && endPoint.y < c2.y && endPoint.y > c1.y)
  {
    //printf("slash");
    return true;
  }
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
    if ((endPoint - startBase).Magnitude() + boxB->Extents.Magnitude()*.9 > (boxTrans->GetPositionXY() - startBase).Magnitude()
        && !((startBase.x < endPoint.x) ^ (startBase.x < boxTrans->GetPositionXY().x))
        && !((startBase.y < endPoint.y) ^ (startBase.y < boxTrans->GetPositionXY().y)))
    {
      //printf("Slash Slash Slash !!!!\n");
      return true;
    }
  }
	return false;


}

std::vector <GameObjectComposition*> LoopAll(Vec2D start, Vec2D end)
{
	//if (start == Vec2D(0.0f, 0.0f) && end == Vec2D(0.0f, 0.0f))
		

	std::vector<GameObjectComposition*> collidedObj;

	std::map<int, GameObjectComposition*>::iterator it = FACTORY->gameObjs.begin();
	int size = FACTORY->gameObjs.size();

	for (; it != FACTORY->gameObjs.end(); ++it)
	{
		//std::cout << it->second->GetId() << std::endl;
		ShapeAAB* shape = (ShapeAAB*)it->second->GetComponent(CT_ShapeAAB);
		if (shape != NULL)
			if (line_rectangle_collide(start, end, shape))
			{
				std::cout << it->second->GetName() << std::endl;
				//std::cout << "Im in loop" << std::endl;
				collidedObj.push_back(it->second);
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