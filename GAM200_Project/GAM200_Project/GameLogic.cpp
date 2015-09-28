///////////////////////////////////////////////////////////////////////////////////////
//
//	Game Logic
//	Simple game logic for demo. A good way to approach understand the game sample
//	is to walk through all the code in game logic and follow the execution through
//	the rest of the engine.
//	
//	Authors: Chris Peters, Benjamin Ellinger
//	Copyright 2010, Digipen Institute of Technology
//
///////////////////////////////////////////////////////////////////////////////////////


#include "GameLogic.h"
#include "./physicsLib//Transform.h"
#include "./physicsLib/Body.h"
#include "./physicsLib/primitive.h"
#include "./engineGraphics/Sprite.h"
#include "./engineGraphics/Camera.h"
#include "./gameComponents/objFactory.h"
#include "./engineGraphics/graphicsManager.h"

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  Texture textureBackground = Texture("resources/background.png");
  Texture textureSmiley = Texture("resources/Smiley1.png");


  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  camera->AddComponent(CT_Camera, new Camera());
  camera->Initialize();

  GOC * background = FACTORY->makeObject("background");
  Transform * transform = new Transform();
  transform->SetPosition(0, 0, 1);
  transform->SetScale(6, 4, 0);
  background->AddComponent(CT_Transform, transform);
  Sprite * sprite = new Sprite(*(graphics->coreShader));
  sprite->texture = textureBackground;
  background->AddComponent(CT_Sprite, sprite);

  GOC * smileyObj = FACTORY->makeObject("dude");
  Transform * transform2 = new Transform();
  transform2->SetPosition(0, 0, 0);
  Sprite * sprite2 = new Sprite(*(graphics->coreShader));
  sprite2->texture = textureSmiley;
  smileyObj->AddComponent(CT_Transform, transform2);
  smileyObj->AddComponent(CT_Transform, sprite2);
  
  camera->Initialize();
  smileyObj->Initialize();
  background->Initialize();
}

GameLogic::GameLogic()
{

}

GameLogic::~GameLogic()
{
}

void GameLogic::Update(float dt)
{

}