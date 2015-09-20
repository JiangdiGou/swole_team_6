#include "baseObject.h"
#include <stdlib.h>
#include <vector>

class objFactory
{
private:
  std::vector<int> objIDs;
public:
  gameObject* makeObject(std::string Name);
};