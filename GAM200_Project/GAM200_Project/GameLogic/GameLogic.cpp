#include "GameLogic.h"
#include ".././physicsLib//Transform.h"
#include ".././physicsLib/Body.h"
#include ".././engineGraphics/Sprite.h"
#include ".././engineGraphics/Camera.h"
#include ".././gameComponents/objFactory.h"
#include ".././engineGraphics/graphicsManager.h"
#include ".././WindowsSystem.h"
#include "../physicsLib/BinaryMap.h"
#include "../physicsLib/PlayerState.h"
#include "../mouseVector.h"
#include "../reactive.h"
#include "PlayerTag.h"
#include "HealthManager.h"
#include "../ZilchComponent.h"

#include <ctime>

//Our global pointer to the game.
GameLogic* LOGIC = NULL;

void GameLogic::Initialize()
{
  createLevel("resources/Levels/Level1.txt");
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

void GameLogic::createLevel(std::string levelPath)
{
  FACTORY->loadLevelFrom(levelPath);

  //SET UP CAMERA
  GOC * camera = FACTORY->makeObject("GAMECAMERA");
  camera->AddComponent(CT_Transform, new Transform());
  Camera *mainCamera = new Camera(*(GRAPHICS->getCoreShader()));
  camera->AddComponent(CT_Camera, mainCamera);
#ifdef EDITOR
  mainCamera->followingPlayer = false;
  mainCamera->editorMode = true;
#endif
  //Saves camera
  camera->Initialize();
  GRAPHICS->setMainCamera(mainCamera);

  //SET UP PLAYER
  GOC * player = FACTORY->makeObject("GAMEPLAYER");
  //Transform
  Transform * transformPlayer = new Transform();
  transformPlayer->SetPosition(2, 6, 0);
  transformPlayer->SetScale(Vector2(3, 3));
  player->AddComponent(CT_Transform, transformPlayer);
  //Shape
  ShapeAAB * boxColliderPlayer = new ShapeAAB();
  boxColliderPlayer->Extents = Vec2D(0.2f * transformPlayer->GetScale().x, 0.45f * transformPlayer->GetScale().y);
  player->AddComponent(CT_ShapeAAB, boxColliderPlayer);
  //Body
  Body * bodyPlayer = new Body();
  bodyPlayer->Mass = 3.0f;
  bodyPlayer->Restitution = 0.3f;
  bodyPlayer->Friction = 0.0f;
  player->AddComponent(CT_Body, bodyPlayer);
  //Editable
#ifdef EDITOR
  Editable* editable = new Editable(false);
  player->AddComponent(CT_Editable, editable);
#endif
  //Controller
  PlayerState * controller = new PlayerState();
  player->AddComponent(CT_PlayerState, controller);
  //Sound Emitter
  SoundEmitter* playerSound = new SoundEmitter();
  player->AddComponent(CT_SoundEmitter, playerSound);
  //Sprite
  Sprite * spritePlayer = new Sprite();
  spritePlayer->setTexture("Character");
  spritePlayer->flipSprite = false;
  player->AddComponent(CT_Sprite, spritePlayer);  
  //EXAMPLE ZILCH COMP
  OurZilchComponent* exampleZilch = new OurZilchComponent("EXAMPLE", CTZ_Example);
  //OurZilchComponent* exampleZilch = new ou;
  player->AddComponent(CT_OurZilchComponent, exampleZilch);
  MouseVector *vectTest = new MouseVector();
  camera->AddComponent(CT_MouseVector, vectTest);
  //HealthManager
  HealthManager* healthManager = new HealthManager();
  player->AddComponent(CT_HealthManager, healthManager);

  //Saves Player
  LOGIC->player = player;

  FACTORY->loadEntities(appendEnt(levelPath));
  FACTORY->createTiles();
  FACTORY->initializeObjects();
}

void GameLogic::Update(float dt)
{
  
}