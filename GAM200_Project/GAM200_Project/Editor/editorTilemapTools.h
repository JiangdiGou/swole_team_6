#ifndef EDITORTILEMAPTOOLS_H
#define EDITORTILEMAPTOOLS_H

#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"

class EditorTilemapTools
{
public:
  EditorTilemapTools();

  void handleTilemapTools();
};

#endif