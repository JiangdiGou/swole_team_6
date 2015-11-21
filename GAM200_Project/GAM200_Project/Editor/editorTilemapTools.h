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
#include "editorModule.h"

class EditorTilemapTools : public EditorModule
{
public:
  EditorTilemapTools();
  void handle() override;
  void init() override;
  void changeTile(GameObjectComposition* tile, bool setEmpty = false);

  bool isActive() { return active; };

private:
  bool active = false;

  TextureAtlas* atlas;

  std::string currentTexture;
  ImVec2 currentTopLeft;
  ImVec2 currentBotRight;

  void emptyTilesVisible(bool visibility);

  //Currently doesn't work. Also this hsould be add to recent list or something 
  void AddToPreviousArray(const std::string &textureName, ImVec2 topLeft, ImVec2 topRight);
  std::list<std::string> recentTextures;
  std::list<ImVec2> recentTopLefts;
  std::list<ImVec2> recentBotRights;
};

#endif