#include "gameLevel.h"
#include "Utilities.h"

//effectively a multi-variable setter
void gameLevel::loadLevelFromFile(std::string fileName)
{
  data = std::fstream(fileName.c_str());
  /*guaranteed:
  L0: LevelName header
  L1: LevelName data
  L2: ArraySpecs header
  L3,L4: Width of level, height of level
  (for all intents and purposes, nothing else is guaranteed)
  */
}