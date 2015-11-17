#ifndef EDITORLEVELTOOLS_H
#define EDITORLEVELTOOLS_H

enum EditorLevelState { IDLE, CREATINGLEVEL, LOADINGLEVEL, INLEVEL };


#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"

class EditorLevelTools
{
public:
  EditorLevelTools();
  void handleLevelTools();

private:
  void generateTextureKey(std::string levelName);
  void EditorLevelTools::createLevelFileFromArray(std::string levelName, int width, int height);
  void EditorLevelTools::createEmptyLevelFile(std::string levelName, int width, int height);
  
  std::string currentMessage;
  EditorLevelState state;

  void fetchTextures();
  std::vector<std::string> textureNames;
};
class EditorLevelTools;

#endif