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
#include "mouseVector.h"

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  FACTORY->loadLevelFrom("BetaLevel.txt");


  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  Camera *mainCamera = new Camera(*(GRAPHICS->getCoreShader()));
  mouseVector *vectTest = new mouseVector();
  camera->AddComponent(CT_MouseVector, vectTest);
  camera->AddComponent(CT_Camera, mainCamera);
  camera->Initialize();
  //This move is so that the bottom left corner is 0,0
  mainCamera->move(glm::vec3(4.5, 2.25, 0));

  GRAPHICS->setMainCamera(mainCamera);

  FACTORY->createTiles();


  //PLAYER
  GOC * player = FACTORY->makeObject("player");
  Transform * transformPlayer = new Transform();
  transformPlayer->SetPosition(2, 6, 0);
  //transformPlayer->SetScale(Vector2(1.0, 1.0));
  player->AddComponent(CT_Transform, transformPlayer);
  Body * bodyPlayer = new Body();
  bodyPlayer->Mass = 3.0f;
  bodyPlayer->Restitution = 0.3f;
  bodyPlayer->Friction = 0.0f;
  ShapeAAB * boxColliderPlayer = new ShapeAAB();
  boxColliderPlayer->Extents = Vec2D(.5, .5);
  bodyPlayer->BodyShape = boxColliderPlayer;

  player->AddComponent(CT_Body, bodyPlayer);
  player->AddComponent(CT_ShapeAAB, boxColliderPlayer);
  PlayerState * controller = new PlayerState();
  player->AddComponent(CT_PlayerState, controller);

  Sprite * spritePlayer = new Sprite();
  spritePlayer->texture = GRAPHICS->getSpriteAtlas()->textures["Character"];
  spritePlayer->flipSprite = false;
  player->AddComponent(CT_Sprite, spritePlayer);

  LOGIC->player = player;


  // ground
  GOC * blackObj2 = FACTORY->makeObject("");
  Transform * transform = new Transform();
  transform->SetPosition(8, 7, 0);
  blackObj2->AddComponent(CT_Transform, transform);
  Body * body = new Body();
  body->Mass = 6.0f;
  body->Restitution = 0.3f;
  body->Friction = 0.0f;
  ShapeAAB * box = new ShapeAAB();
  box->Extents = Vec2D(0.5, 0.5);
  body->BodyShape = box;
  blackObj2->AddComponent(CT_Body, body);
  if (blackObj2 && box && body && body->IsStatic == false)
  {
    std::cout << "I exist" << std::endl;
  }
  //  blackObj2->InitPosition = (whatever, whatever, whatever);
  //Transform * transform6 = new Transform();
  //
  //transform6->SetPosition(4, 1, 0);

  Sprite * sprite5 = new Sprite();
  sprite5->texture = GRAPHICS->getSpriteAtlas()->textures["ExampleSpriteSheet"];
  sprite5->color = glm::vec4(0, 0, 1, 1);
  blackObj2->AddComponent(CT_Sprite, sprite5);
  blackObj2->AddComponent(CT_ShapeAAB, box);


  //down 1
  //GOC * bo1 = FACTORY->makeObject("");
  //Transform * transformbo = new Transform();
  //transformbo->SetPosition(12, 1, 0);
  //bo1->AddComponent(CT_Transform, transformbo);
  //Body * bodybo = new Body();
  //bodybo->Mass = 6.0f;
  //bodybo->Restitution = 0.3f;
  //bodybo->Friction = 0.3f;
  //ShapeAAB * boxbo = new ShapeAAB();
  //boxbo->Extents = Vec2D(0.5, 0.5);
  //bodybo->BodyShape = boxbo;
  //bo1->AddComponent(CT_Body, bodybo);
  //
  ////  blackObj2->InitPosition = (whatever, whatever, whatever);
  ////Transform * transform6 = new Transform();
  ////
  ////transform6->SetPosition(4, 1, 0);
  //
  //Sprite * spritebo = new Sprite();
  //spritebo->texture = graphics->spriteAtlas.textures[std::string("ExampleSpriteSheet")];
  //spritebo->color = glm::vec4(0, 0, 1, 1);
  //bo1->AddComponent(CT_Sprite, spritebo);
  //bo1->AddComponent(CT_ShapeAAB, boxbo);


  // 1
  GOC * blackObj3 = FACTORY->makeObject("");
  Transform * transform1 = new Transform();
  transform1->SetPosition(4, 1, 0);
  blackObj3->AddComponent(CT_Transform, transform1);
  Body * body1 = new Body();
  body1->Mass = 0.0f;
  body1->Restitution = 0.3f;
  body1->Friction = 0.3f;
  ShapeAAB * box1 = new ShapeAAB();
  box1->Extents = Vec2D(0.5, 0.5);
  body1->BodyShape = box1;
  blackObj3->AddComponent(CT_Body, body1);
  if (blackObj3 && box1 && body1 && body1->IsStatic == false)
  {
    std::cout << "I exist 1" << std::endl;
  }
  //  blackObj3->InitPosition = (whatever, whatever, whatever);
  //Transform * transform6 = new Transform();
  //
  //transform6->SetPosition(4, 1, 0);

  Sprite * sprite6 = new Sprite();
  sprite6->texture = GRAPHICS->getSpriteAtlas()->textures["ExampleSpriteSheet"];
  sprite6->color = glm::vec4(1, 1, 0, 1);
  blackObj3->AddComponent(CT_Sprite, sprite6);
  blackObj3->AddComponent(CT_ShapeAAB, box1);


  // 2
  //GOC * blackObj4 = FACTORY->makeObject("");
  //Transform * transform2 = new Transform();
  //transform2->SetPosition(13, 2, 0);
  //blackObj4->AddComponent(CT_Transform, transform2);
  //Body * body2 = new Body();
  //body2->Mass = 0.0f;
  //body2->Restitution = 0.3f;
  //body2->Friction = 0.3f;
  //ShapeAAB * box2 = new ShapeAAB();
  //box2->Extents = Vec2D(0.5, 0.5);
  //body2->BodyShape = box2;
  //blackObj4->AddComponent(CT_Body, body2);
  //if (blackObj4 && box2 && body2 && body2->IsStatic == false)
  //{
  //	std::cout << "I exist 1" << std::endl;
  //}
  ////  blackObj3->InitPosition = (whatever, whatever, whatever);
  ////Transform * transform6 = new Transform();
  ////
  ////transform6->SetPosition(4, 1, 0);
  //
  //Sprite * sprite7 = new Sprite();
  //sprite7->texture = graphics->spriteAtlas.textures[std::string("ExampleSpriteSheet")];
  //sprite7->color = glm::vec4(0, 0, 1, 1);
  //blackObj4->AddComponent(CT_Sprite, sprite7);
  //blackObj4->AddComponent(CT_ShapeAAB, box2);


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

  //player = Fbox;

  FACTORY->intializeObjects();
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
    if (CharacterMessage->keyStatus == keyStatus::KEY_PRESSED)
      switch (CharacterMessage->character)
    {
      std::cout << "char msg char is " << CharacterMessage->character;
      case 'a':
      {

      }
      case 'd':
      {
        std::cout << "ddd" << std::endl;
        Sprite* playerSprite = LOGIC->player->has(Sprite);

        playerSprite->texture = GRAPHICS->getSpriteAtlas()->textures["CharacterRun"];
        break;
      }
    }
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