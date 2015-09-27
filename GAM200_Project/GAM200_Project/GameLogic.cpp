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

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  camera->AddComponent(CT_Camera, new Camera());
  camera->Initialize();

  GOC * gameObject = FACTORY->makeObject("dude");
  Transform * transform = new Transform();
  transform->SetPosition(0, 0, 0);
  gameObject->AddComponent(CT_Transform, transform);
  RigidBody * body = new RigidBody();
  body->mass = 0.0f;
  body->restitution = 0.3f;
  Circle * guyBody = new Circle();
  gameObject->AddComponent(CT_RigidBody, body);

  Sprite * sprite = new Sprite();
  gameObject->AddComponent(CT_Sprite, sprite);

  gameObject->Initialize();
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