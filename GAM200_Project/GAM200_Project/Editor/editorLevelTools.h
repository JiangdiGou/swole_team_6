#ifndef EDITORLEVELTOOLS_H
#define EDITORLEVELTOOLS_H

#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"
#include "editorModule.h"
#include "../Utilities.h"

//These could probably inherit from an editor module or something. eventually. 
class EditorLevelTools : public EditorModule
{
public:
  EditorLevelTools();
  void handle() override;
  void init() override;
  void levelNameUpdate();

private:
  //Heavy lifting functions
  void createLevelFileFromArray(std::string levelName, int width, int height);
  void createEmptyLevelFile(std::string levelName, int width, int height);
  void createBlankEntFile(std::string levelName);
  bool saveEntities(std::string levelName);

  //Helpers 
  bool checkFilename(std::string filename, bool checkContentsAndKey = false);
  bool checkLevelDimensions();
  
  std::string currentMessage;

  char levelPathInput[256] {};
  int levelDimensionInput[2];
};
class EditorLevelTools;

#endif