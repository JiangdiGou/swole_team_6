#include "objFactory.h"
#include <random>

gameObject* objFactory::makeObject(std::string Name)
{
  gameObject *toReturn = new gameObject(Name);

  std::mt19937 init_generator;//Mersenne Twister 19937 generator
  init_generator.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> idgen(1, 2147483647);

  int gen = idgen(init_generator);

  while (std::find(objIDs.begin(), objIDs.end(), gen) != objIDs.end())
  {
    //already using gen
    gen = idgen(init_generator);
  }

  toReturn->setObjID(gen);
  return toReturn;
}
