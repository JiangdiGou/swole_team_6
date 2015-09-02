/******************************************************************************/
/*!
 \file   levelEditor.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the interface for the LevelEditor.
 */
/******************************************************************************/

#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "gameLevel.h"
#include <string>
#include <vector>

class levelEditor
{
private:
  std::vector<std::string> validCommands;
  int numCommands;

  std::string fileName;
  gameLevel gameLevel;

public:
  levelEditor();
  void loadLevelFrom(std::string fileName);
  void editingRoutine();
  void cmdHelp();
  void cmdHelp(std::string command);
  bool cmdSingle(char tile, int x, int y, bool mode);
  void saveLevel();
};
#endif