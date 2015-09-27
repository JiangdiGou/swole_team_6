//author Nolan Yoo

#include "../Composition.h"
#include <stdlib.h>
#include <vector>
#include "../System.h"

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory : public ISystem
{
private:
  std::vector<int> objIDs;
  std::vector<GameObjectComposition*> gameObjs;
public:
  objFactory();
  GameObjectComposition* makeObject(std::string Name);
  void destroyObject(int killID);
  void destroyAllObjects();
  // Overloaded methods
  void Initialize();// override;
  void Update(float dt);//override;
  void Shutdown();// override;

};
extern objFactory * FACTORY;

#endif