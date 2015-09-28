//author Nolan Yoo

#include "objFactory.h"
#include <random>

#include "../AssertionError/AssertionError.h"
bool FACTORY_EXISTS;
objFactory::objFactory()
{
  FACTORY = this;
  FACTORY_EXISTS = true;
}

GameObjectComposition* objFactory::makeObject(std::string Name)
{
  GameObjectComposition *toReturn = new GameObjectComposition();

  std::mt19937 init_generator;//Mersenne Twister 19937 generator
  init_generator.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> idgen(1, 2147483647);

  int gen = idgen(init_generator);

  while (gameObjs[gen] != NULL)
  {
    //already using gen
    gen = idgen(init_generator);
  }

  toReturn->ObjectId = gen;
  gameObjs[gen] = toReturn;
  return toReturn;
}

void objFactory::destroyObject(int killID)
{
  if (gameObjs[killID] == NULL)
  {
    //already using gen
    throw AssertionError(std::string("Object ID " + std::to_string(killID)
                                     +" is not destroyable."
                                     ));
  }
  else
  {
    gameObjs.at(killID)->~GameObjectComposition();
    gameObjs.erase(killID);
  }
}
void objFactory::destroyAllObjects()
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    destroyObject(it->first);
  }

  gameObjs.clear();
}
// Overloaded methods
void objFactory::Initialize()
{

}
void objFactory::Update(float dt)
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    it->second->Update();
  }
}
void objFactory::Shutdown()
{

}