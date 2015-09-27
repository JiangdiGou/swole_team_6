//author Nolan Yoo

#include "objFactory.h"
#include <random>

#include "../AssertionError/AssertionError.h"

objFactory::objFactory()
{
  
}

GameObjectComposition* objFactory::makeObject(std::string Name)
{
  GameObjectComposition *toReturn = new GameObjectComposition();

  std::mt19937 init_generator;//Mersenne Twister 19937 generator
  init_generator.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> idgen(1, 2147483647);

  int gen = idgen(init_generator);

  while (std::find(objIDs.begin(), objIDs.end(), gen) != objIDs.end())
  {
    //already using gen
    gen = idgen(init_generator);
  }

  toReturn->ObjectId = gen;
  objIDs.push_back(gen);
  gameObjs.push_back(toReturn);
  return toReturn;
}

void objFactory::destroyObject(int killID)
{
  if (std::find(objIDs.begin(), objIDs.end(), killID) == objIDs.end())
  {
    //already using gen
    throw AssertionError(std::string("Object ID " + std::to_string(killID)
                                     +" is not destroyable."
                                     ));
  }
  else
  {
    std::vector<int>::iterator pos = std::find(objIDs.begin(), objIDs.end(), killID);
    int whereAt = pos - objIDs.begin();
    objIDs.erase(pos);
    gameObjs.at(whereAt)->~GameObjectComposition();
  }
}
void objFactory::destroyAllObjects()
{
  std::vector<int>::iterator it = objIDs.begin();
  for (; it != objIDs.end(); ++it)
    destroyObject(*it);
}
// Overloaded methods
void objFactory::Initialize()
{

}
void objFactory::Update(float dt)
{

}
void objFactory::Shutdown()
{

}