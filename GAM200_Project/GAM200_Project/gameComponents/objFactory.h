//author Nolan Yoo

#include "../Composition.h"
#include <map>
#include "../System.h"

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory : public ISystem
{
private:
  std::map<int, GameObjectComposition*> gameObjs;//id, Game object
public:
  objFactory();
  GameObjectComposition* makeObject(std::string Name);
  void destroyObject(int killID);
  void destroyAllObjects();
  // Overloaded methods
  void Initialize();// override;
  void Update(float dt);//override;
  void Shutdown();// override;
  void objFactory::SendMessages(Message * message);

};
extern objFactory * FACTORY;
extern bool FACTORY_EXISTS;

#endif