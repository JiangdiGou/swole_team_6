#include "levelEditor.h"
#include "Utilities.h"
#include <fstream>

using std::string;

void levelEditor::loadLevelFrom(std::string fileName)
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

  this->gameLevel.levelName = levelName;
  this->gameLevel.levelWidth = arrayX;
  this->gameLevel.levelHeight = arrayY;
  this->gameLevel.tileMap = tileMap;
  this->gameLevel.entityMap = entityMap;
  this->gameLevel.printLevel();
}

void levelEditor::saveLevelTo(std::string fileName)
{
}