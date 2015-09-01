#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "gameLevel.h"
#include <string>
#include <vector>

class levelEditor
{
private:
  std::vector<std::string> validCommands;
  gameLevel gameLevel;

public:
  levelEditor();
  void loadLevelFrom(std::string fileName);
  void editingRoutine();
  void cmdHelp(std::string command);
  void saveLevelTo(std::string fileName);
};
#endif