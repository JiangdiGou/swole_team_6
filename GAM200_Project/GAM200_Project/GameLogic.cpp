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

  //GOC * background = FACTORY->makeObject("background");
  //Transform * transform = new Transform();
  //transform->SetPosition(0, 0, 1);
  //transform->SetScale(6, 4, 0);
  //background->AddComponent(CT_Transform, transform);
  //Sprite * sprite = new Sprite(*(graphics->coreShader));
  //sprite->texture = textureBackground;
  //background->AddComponent(CT_Sprite, sprite);


  //circle
  //GOC * greenObj = FACTORY->makeObject("greenGuy");
  //Transform * transform2 = new Transform();
  //transform2->SetPosition(0, 0, 0);
  //Sprite * sprite2 = new Sprite();
  //sprite2->texture = graphics->spriteAtlas.textures[std::string("Smiley1")];
  //greenObj->AddComponent(CT_Transform, transform2);
  //greenObj->AddComponent(CT_Sprite, sprite2);

  //GOC * greenObj2 = FACTORY->makeObject("greenGuy2");
  //Transform * transform3 = new Transform();
  //transform3->SetPosition(1, 0, 0);
  //Sprite * sprite3 = new Sprite();
  //sprite3->texture = graphics->spriteAtlas.textures[std::string("Smiley2")];
  //greenObj2->AddComponent(CT_Transform, transform3);
  //greenObj2->AddComponent(CT_Sprite, sprite3);


  //greenObj->AddComponent(CT_Transform, transform2);
  //greenObj->AddComponent(CT_Sprite, sprite2);
  //RigidBody* dudeBody = new RigidBody();
  //dudeBody->isStatic = false;
  //dudeBody->isGhost = false;
  //dudeBody->useGravity = true;
  //greenObj->AddComponent(CT_RigidBody, dudeBody);
  //Circle *dudeCollision = new Circle();

  ////dudeCollision->SetHalfSize(1, 1);
  //greenObj->AddComponent(CT_Circle, dudeCollision);

  //GOC * lalalaObj = FACTORY->makeObject("laGuy");
  //Transform * transformla = new Transform();
  //transformla->SetPosition(-3,1.5, 0);
  //Sprite * spritela = new Sprite(*(graphics->coreShader));
  //spritela->texture = textureIdleGreen;
  //lalalaObj->AddComponent(CT_Transform, transformla);
  //lalalaObj->AddComponent(CT_Sprite, spritela);
  //RigidBody* laBody = new RigidBody();
  ////dudeBody->isGhost = false;
  //laBody->useGravity = false;
  //lalalaObj->AddComponent(CT_RigidBody, laBody);
  //Circle *laCollision = new Circle();
  ////dudeCollision->SetHalfSize(1, 1);
  //lalalaObj->AddComponent(CT_Circle, laCollision);


  //Anoother Boguy
  /*
  GOC * boObj2 = FACTORY->makeObject("boGuy");
  Transform * transformbo2 = new Transform();
  transformbo2->SetPosition(-1, 2, 0);
  Sprite * spritebo2 = new Sprite();
  spritebo2->texture = graphics->spriteAtlas.textures[std::string("Smiley2")];
  boObj2->AddComponent(CT_Transform, transformbo2);
  boObj2->AddComponent(CT_Sprite, spritebo2);
  RigidBody* boObjBody2 = new RigidBody();
  boObjBody2->isStatic = false;
  boObjBody2->isGhost = false;
  boObjBody2->useGravity = true;
  boObj2->AddComponent(CT_RigidBody, boObjBody2);
  AABB* boCollision2 = new AABB();
  boCollision2->SetHalfSize(1, 1);
  boObj2->AddComponent(CT_AABB, boCollision2);
  printf("bo2's velocity: %f, %f", boObjBody2->getVelocity().x, boObjBody2->getVelocity().y);




  GOC * blackObj = FACTORY->makeObject("");
  Transform * transform5 = new Transform();
  transform5->SetPosition(0, -2, 0);
  Sprite * sprite4 = new Sprite();
  sprite4->texture = graphics->spriteAtlas.textures[std::string("ExampleSpriteSheet")];

  blackObj->AddComponent(CT_Transform, transform5);
  blackObj->AddComponent(CT_Sprite, sprite4);
  RigidBody* blackObjBody = new RigidBody();
  blackObjBody->isGhost = false;
  blackObjBody->isStatic = true;
  blackObjBody->useGravity = false;
  //blackObjBody->isKinematic = true;
  if (blackObjBody->isStatic)
  {
	  transform5->SetPosition(0, -2, 0);
  }
  blackObj->AddComponent(CT_RigidBody, blackObjBody);
  AABB* blackCollision = new AABB();
  blackCollision->SetHalfSize(1, 1);
  blackObj->AddComponent(CT_AABB, blackCollision);


  
  //Ground1
  GOC * blackObj2 = FACTORY->makeObject("");
//  blackObj2->InitPosition = (whatever, whatever, whatever);
  Transform * transform6 = new Transform();

  transform6->SetPosition(-1, -2, 0);
  Sprite * sprite5 = new Sprite();
  sprite5->texture = graphics->spriteAtlas.textures[std::string("ExampleSpriteSheet")];

  blackObj2->AddComponent(CT_Transform, transform6);
  blackObj2->AddComponent(CT_Sprite, sprite5);
  RigidBody* blackObjBody2 = new RigidBody();
  blackObjBody2->isGhost = false;
  blackObjBody2->isStatic = true;
  blackObjBody2->useGravity = false;
  if (blackObjBody2->isStatic)
  {
	  transform6->SetPosition(-1,-2,0);
  }
  //blackObjBody->isKinematic = true;
  blackObj2->AddComponent(CT_RigidBody, blackObjBody2);
  AABB* blackCollision2 = new AABB();
  blackCollision2->SetHalfSize(1, 1);
  blackObj2->AddComponent(CT_AABB, blackCollision2);

  player = boObj;
  //player2 = boObj;
  boObj2->Initialize();
  //blueObj->Initialize();
 //greenObj->Initialize();
  blackObj->Initialize(); 
  
  
  ->Initialize();
  //lalalaObj-> Initialize();
  boObj->Initialize();
  blackObj2->Initialize();

  //background->Initialize();*/

//GOC * boObj = FACTORY->makeObject("boGuy");
//Transform * transformbo = new Transform();
//transformbo->SetPosition(4, 3, 0);
//Sprite * spritebo = new Sprite();
//spritebo->texture = graphics->spriteAtlas.textures[std::string("Smiley2")];
//boObj->AddComponent(CT_Transform, transformbo);
//boObj->AddComponent(CT_Sprite, spritebo);
//RigidBody* boObjBody = new RigidBody();
////boObjBody->set(5.0f);
//
////boObjBody->restitution = 0;
//boObjBody->isStatic = false;
//boObjBody->isGhost = false;
//boObjBody->useGravity = true;
//boObj->AddComponent(CT_RigidBody, boObjBody);
//AABB* boCollision = new AABB();
//boCollision->SetHalfSize(1.0f, 1.0f);
//boObj->AddComponent(CT_AABB, boCollision);
//TileMapCollision* boTileCollision = new TileMapCollision();
//boObj->AddComponent(CT_TileMapCollision, boTileCollision);
//PlayerState* playerState = new PlayerState();
//boObj->AddComponent(CT_PlayerState, playerState);


// new falling object
GOC * Fbox = FACTORY->makeObject("");
Transform * transformFbox = new Transform();
transformFbox->SetPosition(4, 4, 0);
Fbox->AddComponent(CT_Transform, transformFbox);
Body * bodyFbox = new Body();
bodyFbox->Mass = 3;
bodyFbox->Restitution = 0.3f;
bodyFbox->Friction = 0.3f;
ShapeAAB * boxFbox = new ShapeAAB();
boxFbox->Extents = Vec2D(.5, .5);
bodyFbox->BodyShape = boxFbox;
//bodyFbox->SetVelocity(Vec2D(0,0));
//bodyFbox->AddForce(Vec2D(0, -3));
Fbox->AddComponent(CT_Body, bodyFbox);
printf("my v%f, %f", bodyFbox->Velocity.x, bodyFbox->Velocity.y);
//bodyFbox->AddForce((Vec2D(0,0) - bodyFbox->Position) * 50);
Vec2D testV = bodyFbox->Velocity;

printf("my pos%f, %f", bodyFbox->Position, bodyFbox->Position.y);

if (Fbox && boxFbox && bodyFbox && bodyFbox->IsStatic == false)
{
	std::cout << "Fbox exist" << std::endl;
	//std::cout << testV << std::endl;
}
//  blackObj2->InitPosition = (whatever, whatever, whatever);
//Transform * transform6 = new Transform();
//
//transform6->SetPosition(4, 1, 0);

Sprite * spriteFbox = new Sprite();
spriteFbox->texture = graphics->spriteAtlas.textures[std::string("sliceTest-1")];
Fbox->AddComponent(CT_Sprite, spriteFbox);




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