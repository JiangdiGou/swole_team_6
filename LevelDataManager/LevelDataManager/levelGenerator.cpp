/******************************************************************************/
/*!
 \file   levelGenerator.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the implementation of the levelGenerator class, which can generate an empty Level in a file.
 */
/******************************************************************************/

#include "levelGenerator.h"
#include "Utilities.h"

void levelGenerator::selectLevelFile()
{
  string fileName;

  std::cout << "Name the level file: ";
  std::cin >> fileName;
  openForEditing(fileName);
}

//create an empty file
void levelGenerator::createEmptyFile(string fileName)
{
  if (fileExists(fileName.c_str()))
  {
    std::cout << "received fileName that already exists: " << fileName << std::endl;
    throw std::invalid_argument("received fileName that already exists: " + fileName);
  }

  std::ofstream outfile(fileName.c_str());
  outfile.close();
}

void levelGenerator::writeLevelName(string levelName)
{
  string dataHeader = "[LevelName]\n";
  editingLevelFile << dataHeader;
  editingLevelFile << levelName << '\n';
}

void levelGenerator::writeLevelSize()
{
  string dataHeader = "[ArraySpecs]\n";
  editingLevelFile << dataHeader;
  editingLevelFile << desiredWidth << '\n';
  editingLevelFile << desiredHeight << '\n';
}

void levelGenerator::writeTileMap()
{
  string dataHeader = "[TileMap]\n";

  editingLevelFile << dataHeader;
  for (int i = 0; i < desiredHeight; i++)
  {
    for (int j = 0; j < desiredWidth; j++)
    {
      editingLevelFile << holdingArray[i][j];
    }
    editingLevelFile << '\n';
  }
}

void levelGenerator::writeEntityMap()
{
  string dataHeader = "[EntityMap]\n";

  editingLevelFile << dataHeader;
  for (int i = 0; i < desiredHeight; i++)
  {
    for (int j = 0; j < desiredWidth; j++)
    {
      editingLevelFile << holdingArray[i][j];
    }
    editingLevelFile << '\n';
  }
}

//attempt to open a file for editing
void levelGenerator::openForEditing(string fileName)
{
  editingLevelFile.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  if (editingLevelFile.fail())
  {
    std::cout << "received fileName couldn't be opened: " << fileName << std::endl;
    throw std::invalid_argument("received fileName couldn't be opened: " + fileName);
  }
  else
  {
    std::cout << "File " << fileName.c_str() << " opened successfully." << std::endl;
  }
}

void levelGenerator::promptWriteLevelName()
{
  string levelName;
  std::cout << "Give the level file an in-game name: ";
  std::cin >> levelName;
  writeLevelName(levelName);
}

string levelGenerator::promptCreateEmptyFile()
{
  string fileName;

  std::cout << "Name the level file: ";
  std::cin >> fileName;

  createEmptyFile(fileName);
  lastFileName.assign(fileName);
  return fileName;
}

void levelGenerator::promptWriteLevelSize()
{
  std::cout << "Width of level in tiles: ";
  std::cin >> desiredWidth;
  std::cout << "Height of level in tiles: ";
  std::cin >> desiredHeight;
  prepareLevelArray();
  writeLevelSize();
  writeTileMap();
  writeEntityMap();
}

bool levelGenerator::openFileEmpty()
{
  //peeking apparently can seek in edge cases where we peeked the last character
  bool toReturn = (editingLevelFile.peek() == std::ifstream::traits_type::eof());
  //close+open cycle for safety
  editingLevelFile.close();
  editingLevelFile.open(lastFileName.c_str());
  return toReturn;
}

void levelGenerator::prepareLevelArray()
{
  holdingArray = new char*[desiredHeight];
  for (int i = 0; i < desiredHeight; i++)
  {
    holdingArray[i] = new char[desiredWidth];
  }

  for (int i = 0; i < desiredHeight; i++)
  {
    for (int j = 0; j < desiredWidth; j++)
    {
      holdingArray[i][j] = '0';
    }
  }
}

void levelGenerator::closeFstream()
{
  if (editingLevelFile.is_open())
  {
    editingLevelFile.close();
  }
}

string levelGenerator::getFileName()
{
  return lastFileName;//no reason for this to have changed during editing
}