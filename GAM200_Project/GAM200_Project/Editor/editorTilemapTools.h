#ifndef EDITORTILEMAPTOOLS_H
#define EDITORTILEMAPTOOLS_H

#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"

class EditorTilemapTools
{
public:
  EditorTilemapTools();
  void handleTilemapTools();

private:
  std::string currentTexture;
  ImVec2 currentTopLeft;
  ImVec2 currentBotRight;


  void AddToPreviousArray(const std::string textureName, ImVec2 topLeft, ImVec2 topRight);

  std::list<std::string> recentTextures;
  std::list<ImVec2> recentTopLefts;
  std::list<ImVec2> recentBotRights;
};

#endif