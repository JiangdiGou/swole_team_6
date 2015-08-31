#include <string>
#include <fstream>

class gameLevel
{
private:
  std::fstream data;

public:
  std::string levelName;
  int levelWidth;
  int levelHeight;
  char ** tileMap;
  char ** entityMap;

public:
  void printLevel();
  void loadLevelFrom(std::string fileName);
};