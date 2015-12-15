/******************************************************************************/
/*!
\author Conor Lavelle

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef EDITORENTITYTOOLS_H
#define EDITORENTITYTOOLS_H

#define _CRT_SECURE_NO_WARNINGS
#define TOTALCOMPONENTS 26

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
#include "../GameLogic/PlayerTag.h"
#include "../GameLogic/HUDcomponent.h"
#include "../GameLogic/BadEnemyAI.h"
#include "../GameLogic/HealthManager.h"
#include "../GameLogic/GameReactive.h"
#include "../GameLogic/PlayerHealthBar.h"
#include "../GameLogic/PlayerAttack.h"
#include "../GameLogic/PauseMenuButton.h"
#include "../GameLogic/LoadLevel.h"
#include "../GameLogic/EnemyHealthManager.h"
#include "../GameLogic/WinLogic.h"
#include "../GameLogic/TutorialLogic.h"
#include "../GameLogic/QuitGame.h"
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
  float tweakf3_1[3];
  float tweakf3_2[3];
  float tweakF;
  float tweakF4[4];
  int tweakI = 0;

  GameObjectComposition* focus;
  char newEntityName[256];

  char tweakableText[256]; 

  void showTweakables(ComponentTypeId type);
  GameComponent* getFocusComponent(ComponentTypeId type);

  static const char* components[TOTALCOMPONENTS];

  int currentItem = 1;

};

#endif