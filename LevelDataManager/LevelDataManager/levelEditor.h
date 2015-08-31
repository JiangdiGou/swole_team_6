#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H
#include <string>

class levelEditor
{
private:
  bool level;

public:
  void loadLevelFrom(std::string fileName);
  void saveLevelTo(std::string fileName);
};
#endif