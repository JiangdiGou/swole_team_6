#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include "gameLevel.h"
#include <string>

class levelEditor
{
private:
  gameLevel gameLevel;

public:
  void loadLevelFrom(std::string fileName);
  void saveLevelTo(std::string fileName);
};
#endif