/******************************************************************************/
/*!
 \file   gameLevel.h
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the interface for the gameLevel class.
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <string>
#include <fstream>

class gameLevel
{
private:
  std::fstream data;

public:
  std::string fileName;
  std::string levelName;
  int levelWidth;
  int levelHeight;
  char ** tileMap;
  char ** entityMap;

  bool validPoint(int x, int y);

public:
  void printLevel();
  void loadLevelFrom(std::string fileName);

  bool changeTile(char tile, int x, int y);
  bool changeEntity(char entity, int x, int y);
  void insertCol(int x, int count);
  void insertRow(int y, int count);
};

#endif