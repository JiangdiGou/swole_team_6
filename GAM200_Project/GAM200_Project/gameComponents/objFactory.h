#include "baseObject.h"
#include <stdlib.h>
#include <vector>

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory
{
private:
  std::vector<int> objIDs;
  std::vector<gameObject*> gameObjs;
public:
  objFactory();
  gameObject* makeObject(std::string Name);
  void destroyObject(int killID);

};
extern objFactory * FACTORY;

#endif