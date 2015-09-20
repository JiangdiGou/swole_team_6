//
//  baseObject.cpp
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  Copyright (c) 2015 Nolan Yoo. All rights reserved.
//

#include "baseObject.h"

gameObject::gameObject(std::string name)
{
  this->name = name;
}

int gameObject::getObjID()
{
  return this->objID;
}

void gameObject::setObjID(int newID)
{
  this->objID = newID;
}