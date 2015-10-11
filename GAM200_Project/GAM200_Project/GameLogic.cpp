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
#include "./WindowsSystem.h"

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  Texture textureBackground = Texture("resources/background.png");
  Texture textureSmiley = Texture("resources/Smiley1.png");
  Texture textureIdleGreen = Texture("resources/courier.png", 26, 43, 83, 100, 0, 0);
  Texture textureRunGreen = Texture("resources/courier.png", 26, 43, 83, 100, 0, 0);
  textureIdleBlue = new Texture("resources/NewRunStuff.png", 4, 64, 64, 100, 0, 128);
  textureRunBlue = new Texture("resources/NewRunStuff.png", 8, 64, 64, 100, 0, 192);
  

  GOC * camera = FACTORY->makeObject("Camera");
  camera->AddComponent(CT_Transform, new Transform());
  camera->AddComponent(CT_Camera, new Camera((graphics->coreShader)));
  camera->Initialize();

  //GOC * background = FACTORY->makeObject("background");
  //Transform * transform = new Transform();
  //transform->SetPosition(0, 0, 1);
  //transform->SetScale(6, 4, 0);
  //background->AddComponent(CT_Transform, transform);
  //Sprite * sprite = new Sprite(*(graphics->coreShader));
  //sprite->texture = textureBackground;
  //background->AddComponent(CT_Sprite, sprite);

  GOC * greenObj = FACTORY->makeObject("greenGuy");
  Transform * transform2 = new Transform();
  transform2->SetPosition(0, 3, 0);
  Sprite * sprite2 = new Sprite();
  sprite2->texture = textureIdleGreen;
  greenObj->AddComponent(CT_Transform, transform2);
  greenObj->AddComponent(CT_Sprite, sprite2);
  RigidBody* dudeBody = new RigidBody();
  dudeBody->isGhost = false;
  dudeBody->useGravity = true;
  greenObj->AddComponent(CT_RigidBody, dudeBody);
  Circle *dudeCollision = new Circle();
  //dudeCollision->SetHalfSize(1, 1);
  greenObj->AddComponent(CT_Circle, dudeCollision);

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


  GOC * boObj = FACTORY->makeObject("boGuy");
  Transform * transformbo = new Transform();
  transformbo->SetPosition(3, 0, 0);
  Sprite * spritebo = new Sprite();
  spritebo->texture = *textureIdleBlue;
  boObj->AddComponent(CT_Transform, transformbo);
  boObj->AddComponent(CT_Sprite, spritebo);
  RigidBody* boObjBody = new RigidBody();
  dudeBody->isGhost = false;
  boObjBody->useGravity = true;
  boObj->AddComponent(CT_RigidBody, boObjBody);
  AABB* boCollision = new AABB();
  boCollision->SetHalfSize(1, 1);
  boObj->AddComponent(CT_AABB, boCollision);


  GOC * text1 = FACTORY->makeObject("blueGuy");
  Transform * transform3 = new Transform();
  transform3->SetPosition(-3.25, 1.5, 0);
  transform3->SetScale(0.25, 0.5, 1);
  text1->AddComponent(CT_Transform, transform3);
  SpriteText * testText = new SpriteText("hi there\nI handle\nnew Lines\nand can have long lines too");
  text1->AddComponent(CT_SpriteText, testText);

  GOC * text2 = FACTORY->makeObject("blueGuy");
  Transform * transform4 = new Transform();
  transform4->SetPosition(0.25, 1.5, 0);
  transform4->SetScale(0.25, 0.5, 1);
  text2->AddComponent(CT_Transform, transform4);
  SpriteText * testText2 = new SpriteText("this is also\ntext");
  text2->AddComponent(CT_SpriteText, testText2);

  GOC * blackObj = FACTORY->makeObject("");
  Transform * transform5 = new Transform();
  transform5->SetPosition(0, -2, 0);
  Sprite * sprite4 = new Sprite();
  sprite4->texture = *textureIdleBlue;
  blackObj->AddComponent(CT_Transform, transform5);
  blackObj->AddComponent(CT_Sprite, sprite4);
  RigidBody* blackObjBody = new RigidBody();
  blackObjBody->isGhost = false;
  blackObjBody->isStatic = true;
  blackObjBody->useGravity = false;
  //blackObjBody->isKinematic = true;
  blackObj->AddComponent(CT_RigidBody, blackObjBody);
  AABB* blackCollision = new AABB();
  blackCollision->SetHalfSize(6, 0.5);
  blackObj->AddComponent(CT_AABB, blackCollision);
  
  player = boObj;
  //player2 = boObj;

  //blueObj->Initialize();
  text1->Initialize();
  text2->Initialize();
  greenObj->Initialize();
  blackObj->Initialize(); 
  camera->Initialize();
  //lalalaObj-> Initialize();
  boObj->Initialize();

  //background->Initialize();
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