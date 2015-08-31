#include "gameLevel.h"
#include "Utilities.h"

using std::string;

void gameLevel::printLevel()
{
  std::cout << "Level Name: " << this->levelName << std::endl;
  std::cout << "Width: " << this->levelWidth << std::endl;
  std::cout << "Height: " << this->levelHeight << std::endl;
  std::cout << "Tile Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
    string garbage(tileMap[i]);
    std::cout << garbage << std::endl;
  }
  std::cout << "Entity Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
    string garbage(entityMap[i]);
    std::cout << garbage << std::endl;
  }
}

//effectively a multi-variable setter
void gameLevel::loadLevelFrom(std::string fileName)
{
  string garbage;
  string levelName;//at line 2
  int arrayX;      //        4
  int arrayY;      //        5
  char**  tileMap;
  char**  entityMap;

  //get line count
  int lineCount;
  std::ifstream tempfile(fileName);
  std::string line;
  for (lineCount = 0; std::getline(tempfile, line); ++lineCount)
    ;//empty for, use for counting only
  tempfile.close();

  //get level name property
  levelName = getLineFromFile(2, fileName);
  //std::cout << levelName;

  //width of tileMap
  garbage = getLineFromFile(4, fileName);
  arrayX = std::stoi(garbage);

  //height of tileMap
  garbage = getLineFromFile(5, fileName);
  arrayY = std::stoi(garbage);

  //load arrays
  tileMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    tileMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 2, fileName);
    strcpy(tileMap[i], garbage.c_str());
  }

  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 1 + 2 + arrayY, fileName);
    strcpy(entityMap[i], garbage.c_str());
  }

  this->levelName = levelName;
  this->levelWidth = arrayX;
  this->levelHeight = arrayY;
  this->tileMap = tileMap;
  this->entityMap = entityMap;
  this->printLevel();
}