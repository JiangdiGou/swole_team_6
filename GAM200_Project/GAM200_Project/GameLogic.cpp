///////////////////////////////////////////////////////////////////////////////////////
//
//	Game Logic
//	Simple game logic for demo. A good way to approach understand the game sample
//	is to walk through all the code in game logic and follow the execution through
//	the rest of the engine.
//	
//	Authors: Chris Peters, Benjamin Ellinger <- did they author this lol? 
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
#include "./WindowsSystem.h"
#include "physicsLib/BinaryMap.h"
#include "physicsLib/PlayerState.h"

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  FACTORY->loadLevelFrom("BetaLevel.txt");

  textureIdleBlue = new Texture("resources/NewRunStuff.png", 4, 64, 64, 100, 0, 128);
  textureRunBlue = new Texture("resources/NewRunStuff.png", 8, 64, 64, 100, 0, 192);
  
  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  Camera *mainCamera = new Camera((graphics->coreShader));
  camera->AddComponent(CT_Camera, mainCamera);
  camera->Initialize();
  //This move is so that the bottom left corner is 0,0
  mainCamera->move(glm::vec3(4.5, 2.25, 0));

  FACTORY->createTiles();

  //PLAYER
  GOC * player = FACTORY->makeObject("player");
  Transform * transformPlayer = new Transform();
  transformPlayer->SetPosition(4, 4, 0);
  player->AddComponent(CT_Transform, transformPlayer);
  Body * bodyPlayer = new Body();
  bodyPlayer->Mass = 3;
  bodyPlayer->Restitution = 0.3f;
  bodyPlayer->Friction = 0.3f;
  ShapeAAB * boxColliderPlayer = new ShapeAAB();
  boxColliderPlayer->Extents = Vec2D(.5, .5);
  bodyPlayer->BodyShape = boxColliderPlayer;

  player->AddComponent(CT_Body, bodyPlayer);
  PlayerState * controller = new PlayerState();
  player->AddComponent(CT_PlayerState, controller);

  Sprite * spritePlayer = new Sprite();
  spritePlayer->texture = graphics->spriteAtlas.textures[std::string("sliceTest-14")];
  player->AddComponent(CT_Sprite, spritePlayer);

  LOGIC->player = player;


// ground
GOC * blackObj2 = FACTORY->makeObject("");
Transform * transform = new Transform();
transform->SetPosition(4, 1,0);
blackObj2->AddComponent(CT_Transform, transform);
Body * body = new Body();
body->Mass = 0.0f;
body->Restitution = 0.3f;
body->Friction = 0.3f;
ShapeAAB * box = new ShapeAAB();
box->Extents = Vec2D(0.5, 0.5);
body->BodyShape = box;
blackObj2->AddComponent(CT_Body, body);
if (blackObj2 && box && body && body->IsStatic == false)
{
	std::cout << "I exist" << std::endl;
}
printf("my v%f", body->Velocity.x);
//  blackObj2->InitPosition = (whatever, whatever, whatever);
//Transform * transform6 = new Transform();
//
//transform6->SetPosition(4, 1, 0);

Sprite * sprite5 = new Sprite();
sprite5->texture = graphics->spriteAtlas.textures[std::string("ExampleSpriteSheet")];
blackObj2->AddComponent(CT_Sprite, sprite5);


//blackObj2->AddComponent(CT_Transform, transform6);
//blackObj2->AddComponent(CT_Sprite, sprite5);
//RigidBody* blackObjBody2 = new RigidBody();
//blackObjBody2->isGhost = false;
//blackObjBody2->SetStatic();
//blackObjBody2->useGravity = false;
//if (blackObjBody2->isStatic)
//{
//	transform6->SetPosition(4, 1, 0);
//}
//blackObjBody->isKinematic = true;
//blackObj2->AddComponent(CT_RigidBody, blackObjBody2);
//AABB* blackCollision2 = new AABB();
//blackCollision2->SetHalfSize(1.0f, 1.0f);
//blackObj2->AddComponent(CT_AABB, blackCollision2);
  FACTORY->intializeObjects();
  //player = Fbox;
}

void GameLogic::SendMessages(Message * m)
{
  switch (m->MessageId)
  {
    // The user has pressed a (letter/number) key, we may respond by creating
    // a specific object based on the key pressed.
  case Mid::CharacterKey:
  {
	  MessageCharacterKey* CharacterMessage = (MessageCharacterKey*)m;
	  switch (CharacterMessage->keyStatus == keyStatus::KEY_PRESSED)
    break;
  }
  case Mid::MouseMove:
  {
    //The mouse has moved, update the mouse's world position
    MouseMove * mouseMove = (MouseMove*)m;
    break;
  }
  case Mid::MouseButton:
  {
    MouseButton * mouse = (MouseButton*)m;
    //Update the world mouse position

    if (mouse->ButtonIsPressed)
    {
      if (mouse->MouseButtonIndex == MouseButton::LeftMouse)
      {
      }
      else if (mouse->MouseButtonIndex == MouseButton::RightMouse)
      {
      }
    }
    else
    {
      //If the mouse has been release let go of the grabbed object
      GrabbedObjectId = 0;
    }
    break;
  }
  }

};


//void GameLogic::SendMessages(Message * message)
//{
//  switch (message->MessageId)
//  {
//    // The user has pressed a (letter/number) key, we may respond by creating
//    // a specific object based on the key pressed.
//  case Mid::CharacterKey:
//  {
//    MessageCharacterKey* messageChar = (MessageCharacterKey*)message;
//    switch (messageChar->character)
//    {
//    case 'd':
//    {
//       setVelocity(0.5, 0);
//    }
//	case 'a':
//	{
//		setVelocity(-0.5, 0);
//	}
//    }
//  }
//  }
//}
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