/******************************************************************************/
/*!
 \file   gameLevel.h
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the interface for the gameLevel class.
 */
/******************************************************************************/

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