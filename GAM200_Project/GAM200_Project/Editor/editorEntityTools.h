#ifndef EDITORENTITYTOOLS_H
#define EDITORENTITYTOOLS_H

#define _CRT_SECURE_NO_WARNINGS
#define TOTALCOMPONENTS 14

#include "imGUI\imgui.h"
#include "../Core.h"
#include <string>
#include <fstream>
#include <iostream>
#include "../engineGraphics/textureAtlas.h"
#include "../engineGraphics/graphicsManager.h"
#include "editorModule.h"
#include "../ComponentTypeIds.h"
#include "../physicsLib/PhysicsManager.h"
#include "../physicsLib/BinaryMap.h"
#include "../physicsLib/PlayerState.h"
#include "../mouseVector.h"
#include "../GameLogic/TestComponent.h"
#include <string.h>
#include <stdio.h>

//For some reason, including these causes errors.
//#include "../physicsLib/PlayerState.h"
//#include "../mouseVector.h"

class EditorEntityTools : public EditorModule
{
public:
  EditorEntityTools();
  void handle() override;
  void init() override;

  GameObjectComposition* getFocus() { return focus; }
  void setFocus(GameObjectComposition* newFocus) { focus = newFocus; }

  GOC* createNewComponent(std::string componentName);

private:
  GameObjectComposition* focus;
  char newEntityName[256];

  char tweakableText[256]; 

  void showTweakables(ComponentTypeId type);
  GameComponent* getFocusComponent(ComponentTypeId type);

  static const const char* components[TOTALCOMPONENTS];

  int currentItem = 1;

};

#endif