#include <string>
#include <fstream>

class gameLevel
{
private:
  std::string levelName;
  int levelWidth;
  int levelHeight;
  char ** tileMap;
  char ** entityMap;
  std::fstream data;

public:
  void loadLevelFromFile(std::string fileName);
};