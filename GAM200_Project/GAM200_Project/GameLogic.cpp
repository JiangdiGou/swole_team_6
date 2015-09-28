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
  Texture textureIdleGreen = Texture("resources/NewRunStuff.png", 4, 64, 64, 100);
  Texture textureRunGreen = Texture("resources/NewRunStuff.png", 8, 64, 64, 100, 0, 64);
  textureIdleBlue = &Texture("resources/NewRunStuff.png", 4, 64, 64, 100, 0, 128);
  textureRunBlue = &Texture("resources/NewRunStuff.png", 8, 64, 64, 100, 0, 192);

  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  camera->AddComponent(CT_Camera, new Camera());
  camera->Initialize();

  /*GOC * background = FACTORY->makeObject("background");
  Transform * transform = new Transform();
  transform->SetPosition(0, 0, 1);
  transform->SetScale(6, 4, 0);
  background->AddComponent(CT_Transform, transform);
  Sprite * sprite = new Sprite(*(graphics->coreShader));
  sprite->texture = textureBackground;
  background->AddComponent(CT_Sprite, sprite);*/

  GOC * greenObj = FACTORY->makeObject("greenGuy");
  Transform * transform2 = new Transform();
  transform2->SetPosition(0, 0, 0);
  Sprite * sprite2 = new Sprite(*(graphics->coreShader));
  sprite2->texture = textureIdleGreen;
  greenObj->AddComponent(CT_Transform, transform2);
  greenObj->AddComponent(CT_Sprite, sprite2);
  RigidBody* dudeBody = new RigidBody();
  dudeBody->isGhost = false;
  dudeBody->useGravity = true;
  greenObj->AddComponent(CT_RigidBody, dudeBody);
  AABB* dudeCollision = new AABB();
  greenObj->AddComponent(CT_Circle, dudeCollision);

  GOC * blueObj = FACTORY->makeObject("blueGuy");
  Transform * transform3 = new Transform();
  transform3->SetPosition(-1, 0, 0);
  Sprite * sprite3 = new Sprite(*(graphics->coreShader));
  sprite3->texture = *textureIdleBlue;
  blueObj->AddComponent(CT_Transform, transform3);
  blueObj->AddComponent(CT_Sprite, sprite3);
  RigidBody* groundBOdy = new RigidBody();
  blueObj->AddComponent(CT_RigidBody, groundBOdy);
  
  player = blueObj;

  blueObj->Initialize();
  greenObj->Initialize();
  camera->Initialize();

  //background->Initialize();
}

GameLogic::GameLogic()
{
  LOGIC = this;
}

GameLogic::~GameLogic()
{
}

void GameLogic::Update(float dt)
{

}