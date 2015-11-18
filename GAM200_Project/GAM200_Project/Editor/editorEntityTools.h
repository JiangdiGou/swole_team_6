#ifndef EDITORENTITYTOOLS_H
#define EDITORENTITYTOOLS_H

#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"
#include "editorModule.h"

class EditorEntityTools : public EditorModule
{
public:
  EditorEntityTools();
  void handle() override;

  GameObjectComposition* getFocus() { return focus; }
  void setFocus(GameObjectComposition* newFocus) { focus = newFocus; }

private:
  GameObjectComposition* focus;

};

#endif