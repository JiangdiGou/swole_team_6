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
  garbage = getLineFromFile(4, fileName);
  arrayY = std::stoi(garbage);

  //load arrays
  tileMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    tileMap[i] = new char[arrayX];
  }
  for (int i = 0; i < arrayY; i++)
  {
    for (int j = 0; j < arrayX; j++)
    {
      tileMap[i][j] = '0';
    }
  }
  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
  }
  for (int i = 0; i < arrayY; i++)
  {
    for (int j = 0; j < arrayX; j++)
    {
      entityMap[i][j] = '0';
    }
  }
}

void levelEditor::saveLevelTo(std::string fileName)
{
}