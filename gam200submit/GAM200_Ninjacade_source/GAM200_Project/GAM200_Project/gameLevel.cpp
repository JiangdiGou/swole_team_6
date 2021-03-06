/******************************************************************************/
/*!
 \file   gameLevel.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the implementation of the gameLevel class. (Quick printing, tileMap, etc).
All content � 2015 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS

#include "gameLevel.h"
#include "Utilities.h"

using std::string;

bool gameLevel::validPoint(int x, int y)
{
  if(x > (this->levelWidth - 1) || y > (this->levelHeight - 1) || x < 0 || y < 0)
  {
    std::cout<<"Invalid tile selection."<<std::endl;
    return false;
  }
  return true;
}

void gameLevel::printLevel()
{
  std::cout << "Level Name: " << this->levelName << std::endl;
  std::cout << "Width: " << this->levelWidth << std::endl;
  std::cout << "Height: " << this->levelHeight << std::endl;
  std::cout << "Tile Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
	  for (int j = 0; j < levelWidth; j++)
	  {
		  std::cout << tileMap[i][j];
	  }
	  std::cout << std::endl;
  }
  std::cout << "Entity Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
	  for (int j = 0; j < levelWidth; j++)
	  {
		  std::cout << entityMap[i][j];
	  }
	  std::cout << std::endl;
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
	std::copy(garbage.begin(), garbage.end(), tileMap[i]);
  }

  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 1 + 2 + arrayY, fileName);
	std::copy(garbage.begin(), garbage.end(), entityMap[i]);
  }

  this->levelName = levelName;
  this->levelWidth = arrayX;
  this->levelHeight = arrayY;
  this->tileMap = tileMap;
  this->entityMap = entityMap;
  this->printLevel();
}

//return false if tile couldn't be changed, true + change tile otherwise
bool gameLevel::changeTile(char tile, int x, int y)
{
  y = this->levelHeight - y - 1;
  if(!this->validPoint(x, y))
  {
    return false;
  }
  this->tileMap[y][x] = tile;
  return true;
}

//return false if tile couldn't be changed, true + change tile otherwise
bool gameLevel::changeEntity(char entity, int x, int y)
{
  //invalid check + reversal
  y = this->levelHeight - y - 1;
  if(!this->validPoint(x, y))
  {
    return false;
  }
  this->entityMap[y][x] = entity;
  return true;
}

void gameLevel::insertCol(int x, int count)
{
  char ** newTileMap;
  char ** newEntityMap;
  int oldHeight = this->levelHeight;
  int oldWidth = this->levelWidth;

  //re-alloc memory
  this->levelWidth = this->levelWidth + count;
  int newWidth = this->levelWidth;

  newTileMap = new char*[oldHeight];
  for (int i = 0; i < oldHeight; i++)
  {
    newTileMap[i] = new char[newWidth];
  }
  newEntityMap = new char*[oldHeight];
  for (int i = 0; i < oldHeight; i++)
  {
    newEntityMap[i] = new char[newWidth];
  }

  //set memory part 0 (give everything a 0)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = 0; j < newWidth; j++)
    {
      newTileMap[i][j] = '0';
      newEntityMap[i][j] = '0';
    }
  }

  //set memory part 1 (before new columns)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = 0; j < x; j++)
    {
      newTileMap[i][j] = tileMap[i][j];
      newEntityMap[i][j] = entityMap[i][j];
    }
  }
  //set memory part 2 (after new columns)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = x; j < oldWidth; j++)
    {
	  newTileMap[i][j + count] = tileMap[i][j];
	  newEntityMap[i][j + count] = entityMap[i][j];
    }
  }

  for (int i = 0; i < oldHeight; i++)
  {
	  delete this->tileMap[i];
	  delete this->entityMap[i];
  }

  delete[] this->tileMap;
  delete[] this->entityMap;

  this->tileMap = newTileMap;
  this->entityMap = newEntityMap;
}

void gameLevel::insertRow(int y, int count)
{
	char ** newTileMap;
	char ** newEntityMap;
	int oldHeight = this->levelHeight;
	int oldWidth = this->levelWidth;

	//re-alloc memory
	this->levelHeight = this->levelHeight + count;
	int newHeight = this->levelHeight;

	newTileMap = new char*[newHeight];
	for (int i = 0; i < newHeight; i++)
	{
		newTileMap[i] = new char[oldWidth];
	}
	newEntityMap = new char*[newHeight];
	for (int i = 0; i < newHeight; i++)
	{
		newEntityMap[i] = new char[oldWidth];
	}

	//set memory part 0 (give everything a 0)
	for (int i = 0; i < newHeight; i++)
	{
		for (int j = 0; j < oldWidth; j++)
		{
			newTileMap[i][j] = '0';
			newEntityMap[i][j] = '0';
		}
	}

	//set memory part 1 (before new columns)
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < oldWidth; j++)
		{
			newTileMap[i][j] = tileMap[i][j];
			newEntityMap[i][j] = entityMap[i][j];
		}
	}
	//set memory part 2 (after new columns)
	for (int i = y; i < oldHeight; i++)
	{
		for (int j = 0; j < oldWidth; j++)
		{
			newTileMap[i + count][j] = tileMap[i][j];
			newEntityMap[i + count][j] = entityMap[i][j];
		}
	}

	for (int i = 0; i < oldHeight; i++)
	{
		delete this->tileMap[i];
		delete this->entityMap[i];
	}

	delete[] this->tileMap;
	delete[] this->entityMap;

	this->tileMap = newTileMap;
	this->entityMap = newEntityMap;
}

