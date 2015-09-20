//
//  baseObject.h
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  Copyright (c) 2015 Nolan Yoo. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "../engineGraphics/glm/vec3.hpp"

class Transform
{
  glm::vec3 translation;
  glm::vec3 rotation;
  glm::vec3 scale;
};

class gameObject
{
private:
  int objID;
  //Sprite sprite;
  std::string name;
  Transform transform;
public:
  gameObject(std::string name);
  int getObjID();
  void setObjID(int newID);
};

