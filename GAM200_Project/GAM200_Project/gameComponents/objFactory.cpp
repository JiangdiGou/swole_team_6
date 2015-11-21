/*!
 ********************************************************************************
 \file    objFactory.cpp
 \author  Nolan Taeksang Yoo
 \author  Gabriel Neumann
 \author  Conor Lavelle
 \par     Contact: nolan\@projectexist.net
 \par     Classes: objFactory
 \brief
 This implements an object factory.
 \remarks
 "Generator" may be a better word. Object IDs are randomly generated.
 All content © 2015 DigiPen (USA) Corporation, all rights reserved.
 *******************************************************************************/

#include "objFactory.h"

#include "../AssertionError/AssertionError.h"
#include "../WindowsSystem.h"
#include "../Serialization/Serialization.h"


bool FACTORY_EXISTS;
int nextID = 0;
int tileNumber = 0;
objFactory::objFactory()
{
  FACTORY = this;
  FACTORY_EXISTS = true;
}

GameObjectComposition* objFactory::makeObject(std::string Name)
{
  GameObjectComposition *toReturn = new GameObjectComposition();


  toReturn->ObjectName = Name;
  toReturn->ObjectId = nextID;
  gameObjs[nextID] = toReturn;
  nextID++;
  return toReturn;
}

void objFactory::destroyObject(int killID)
{
  if (gameObjs[killID] == NULL)
  {
    /* assert that we should never try to destroy an object
       that doesn't exist */
    throw AssertionError(std::string("Object ID " + std::to_string(killID)
                                     +" is not destroyable."
                                     ));
  }
  else
  {
    gameObjs.at(killID)->~GameObjectComposition();
    gameObjs.erase(killID);
  }
}
void objFactory::destroyAllObjects()
{
  std::map<int, GameObjectComposition*>::iterator it;
  for (it = gameObjs.begin(); gameObjs.size() > 0; it = gameObjs.begin())
  {
    destroyObject(it->first);
  }

  gameObjs.clear();
}
void objFactory::SerializeAllObjects(Serializer& str)
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    it->second->SerializeWrite(str);
  }
}
/*std::vector<const GameObjectComposition*> objFactory::GetgameObjs()
{
	std::vector<const GameObjectComposition*> constObjs;
	std::map<int, GameObjectComposition*>::iterator umr;
	for (umr = gameObjs.begin(); umr != gameObjs.end(); umr++)
	{
		constObjs[umr->first] = umr->second;
	}

	return constObjs;
	
}*/
// Overloaded methods
void objFactory::Initialize()
{
}
void objFactory::Update(float dt)
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    it->second->Update(dt);
  }
}
void objFactory::Shutdown()
{

}
void objFactory::SendMessages(Message * message)
{
  switch (message->MessageId)
  {
    // The user has pressed a (letter/number) key, we may respond by creating
    // a specific object based on the key pressed.
  case Mid::CharacterKey:
  {
  }
  case Mid::MouseMove:
  {
  }
  case Mid::MouseButton:
  {
    //MessageCharacterKey* messageChar = (MessageCharacterKey*)message;
    std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
    for (; it != gameObjs.end(); ++it)
    {
      it->second->SendMessages(message);
    }
    break;
  }

    }
}

void objFactory::loadLevelFrom(std::string fileName)
{
  //std::vector<std::string> tokens;
  std::string garbage;
  std::string levelName;//at line 2
  int arrayX;      //        4
  int arrayY;      //        5
  std::string**  tileMap;

  //get line count
  int lineCount;
  std::ifstream tempfile(fileName);
  std::string line;
  for (lineCount = 0; std::getline(tempfile, line); ++lineCount)
    ;//empty for, use for counting only
  tempfile.close();

  //get level name property
  levelName = getLineFromFile(2, fileName);
  //std::cout << levelName;

  //width of tileMap
  garbage = getLineFromFile(4, fileName);
  arrayX = std::stoi(garbage);

  //height of tileMap
  garbage = getLineFromFile(5, fileName);
  arrayY = std::stoi(garbage);

  //load arrays
  tileMap = new std::string*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    tileMap[i] = new std::string[arrayX];

    garbage = getLineFromFile(5 + arrayY-1-i + 2, fileName);   
    //Gets all ints from level file, fills up tilemap array
    std::vector<std::string> results = tokenize(garbage);

    for (int j = 0; j < results.size(); j++)
      tileMap[i][j] = results[j];
  }

  this->levelName = levelName;
  CORE->LevelName = fileName;
  this->levelWidth = arrayX;
  this->levelHeight = arrayY;
  this->tileMap = tileMap;
  this->printLevel();

#ifdef EDITOR
  GUIMGR->updateModules();
#endif
}

void objFactory::createTiles()
{
  //createDefaultTile(0, 0);
  int i, j;
  for (i = 0; i < levelHeight; i++)
  {
    for (j = 0; j < levelWidth; j++)
    {
      std::string texture = (tileMap[i][j]);
      if (texture == "E")
      {
#ifdef EDITOR
        GOC* emptyTile = createTile(j, i, "E");
        Sprite* emptyTileSprite = emptyTile->has(Sprite);
        emptyTileSprite->visible = false;
#endif
      }
      else
        createTile(j, i, texture);

      /*
    case '1':
    createTile(j, i, std::string("sliceTest-207"));
    break;
    case '2':
    createTile(j, i, std::string("sliceTest-72"));
    break;
    case '3':
    createTile(j, i, std::string("sliceTest-246"));
    break;
    case '4':
    createTile(j, i, std::string("sliceTest-181"));
    break;
    case '5':
    createTile(j, i, std::string("sliceTest-165"));
    break;
    }
    */
    }
  }
}

GOC * objFactory::createTile(int positionX, int positionY, std::string textureName)
{
  GOC * newTile = FACTORY->makeObject("newTile" + tileNumber++);
  Transform * tileTransform = new Transform();
  tileTransform->SetPosition(positionX, positionY, 0);
  Sprite * tileSprite = new Sprite();
  tileSprite->texture = GRAPHICS->getSpriteAtlas()->textures[textureName];//TileAtlas
  newTile->AddComponent(CT_Transform, tileTransform);
  newTile->AddComponent(CT_Sprite, tileSprite);

  //Don't want the empty tile to have collision
  if (!(textureName == "E"))
  {
    Body * tileBody = new Body();
    tileBody->Mass = 0;
    tileBody->Restitution = 0.3f;
    tileBody->Friction = 0.0f;
    ShapeAAB * boxCollider = new ShapeAAB();
    boxCollider->Extents = Vec2D(.5, .5);
    tileBody->BodyShape = boxCollider;
    newTile->AddComponent(CT_Body, tileBody);
    newTile->AddComponent(CT_ShapeAAB, boxCollider);
  }

//Adds reactive b/c its a depend of editable.
#ifdef EDITOR
  Reactive* reactive = new Reactive();
  newTile->AddComponent(CT_Reactive, reactive);
  Editable* editable = new Editable();
  newTile->AddComponent(CT_Editable, editable);
#endif
  return newTile;
}

void objFactory::initializeObjects()
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    it->second->Initialize();
  }
}

void objFactory::printLevel()
{
  std::cout << "Level Name: " << this->levelName << std::endl;
  std::cout << "Width: " << this->levelWidth << std::endl;
  std::cout << "Height: " << this->levelHeight << std::endl;
  std::cout << "Tile Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
    for (int j = 0; j < levelWidth; j++)
    {
      std::cout << tileMap[i][j];
    }
    std::cout << std::endl;
  }
}