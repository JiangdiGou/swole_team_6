#include "baseObject.h"
#include <stdlib.h>
#include <vector>

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