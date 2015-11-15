/*!
 ********************************************************************************
 \file    objFactory.cpp
 \author  Nolan Taeksang Yoo
 \author  Gabriel Neumann
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

bool objFactory::validPoint(int x, int y)
{
  if (x > (this->levelWidth - 1) || y > (this->levelHeight - 1) || x < 0 || y < 0)
  {
    std::cout << "Invalid tile selection." << std::endl;
    return false;
  }
  return true;
}

void objFactory::loadLevelFrom(std::string fileName)
{
  std::string garbage;
  std::string levelName;//at line 2
  int arrayX;      //        4
  int arrayY;      //        5
  char**  tileMap;
  char**  entityMap;

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
  tileMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    tileMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + arrayY-1-i + 2, fileName);
    std::copy(garbage.begin(), garbage.end(), tileMap[i]);
  }

  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + arrayY-1-i + 1 + 2 + arrayY, fileName);
    std::copy(garbage.begin(), garbage.end(), entityMap[i]);
  }

  this->levelName = levelName;
  this->levelWidth = arrayX;
  this->levelHeight = arrayY;
  this->tileMap = tileMap;
  this->entityMap = entityMap;
  this->printLevel();
}

void objFactory::createTiles()
{
  //createDefaultTile(0, 0);
  int i, j;
  for (i = 0; i < levelHeight; i++)
  {
    for (j = 0; j < levelWidth; j++)
    {
      int value = (int)(tileMap[i][j] - '0');
#ifdef EDITOR
      if (value == 0)
        createTile(j, i, textureKey[value]);
#endif

      if (value > 0)
        createTile(j, i, textureKey[value]);

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
  if (!(textureName == "EmptyTile"))
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

void objFactory::intializeObjects()
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
  std::cout << "Entity Map:" << std::endl;
  for (int i = 0; i < levelHeight; i++)
  {
    for (int j = 0; j < levelWidth; j++)
    {
      std::cout << entityMap[i][j];
    }
    std::cout << std::endl;
  }
}
//return false if tile couldn't be changed, true + change tile otherwise
bool objFactory::changeTile(char tile, int x, int y)
{
  y = this->levelHeight - y - 1;
  if (!this->validPoint(x, y))
  {
    return false;
  }
  this->tileMap[y][x] = tile;
  return true;
}

//return false if tile couldn't be changed, true + change tile otherwise
bool objFactory::changeEntity(char entity, int x, int y)
{
  //invalid check + reversal
  y = this->levelHeight - y - 1;
  if (!this->validPoint(x, y))
  {
    return false;
  }
  this->entityMap[y][x] = entity;
  return true;
}

void objFactory::insertCol(int x, int count)
{
  char ** newTileMap;
  char ** newEntityMap;
  int oldHeight = this->levelHeight;
  int oldWidth = this->levelWidth;

  //re-alloc memory
  this->levelWidth = this->levelWidth + count;
  int newWidth = this->levelWidth;

  newTileMap = new char*[oldHeight];
  for (int i = 0; i < oldHeight; i++)
  {
    newTileMap[i] = new char[newWidth];
  }
  newEntityMap = new char*[oldHeight];
  for (int i = 0; i < oldHeight; i++)
  {
    newEntityMap[i] = new char[newWidth];
  }

  //set memory part 0 (give everything a 0)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = 0; j < newWidth; j++)
    {
      newTileMap[i][j] = '0';
      newEntityMap[i][j] = '0';
    }
  }

  //set memory part 1 (before new columns)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = 0; j < x; j++)
    {
      newTileMap[i][j] = tileMap[i][j];
      newEntityMap[i][j] = entityMap[i][j];
    }
  }
  //set memory part 2 (after new columns)
  for (int i = 0; i < oldHeight; i++)
  {
    for (int j = x; j < oldWidth; j++)
    {
      newTileMap[i][j + count] = tileMap[i][j];
      newEntityMap[i][j + count] = entityMap[i][j];
    }
  }

  for (int i = 0; i < oldHeight; i++)
  {
    delete this->tileMap[i];
    delete this->entityMap[i];
  }

  delete[] this->tileMap;
  delete[] this->entityMap;

  this->tileMap = newTileMap;
  this->entityMap = newEntityMap;
}

void objFactory::insertRow(int y, int count)
{
  char ** newTileMap;
  char ** newEntityMap;
  int oldHeight = this->levelHeight;
  int oldWidth = this->levelWidth;

  //re-alloc memory
  this->levelHeight = this->levelHeight + count;
  int newHeight = this->levelHeight;

  newTileMap = new char*[newHeight];
  for (int i = 0; i < newHeight; i++)
  {
    newTileMap[i] = new char[oldWidth];
  }
  newEntityMap = new char*[newHeight];
  for (int i = 0; i < newHeight; i++)
  {
    newEntityMap[i] = new char[oldWidth];
  }

  //set memory part 0 (give everything a 0)
  for (int i = 0; i < newHeight; i++)
  {
    for (int j = 0; j < oldWidth; j++)
    {
      newTileMap[i][j] = '0';
      newEntityMap[i][j] = '0';
    }
  }

  //set memory part 1 (before new columns)
  for (int i = 0; i < y; i++)
  {
    for (int j = 0; j < oldWidth; j++)
    {
      newTileMap[i][j] = tileMap[i][j];
      newEntityMap[i][j] = entityMap[i][j];
    }
  }
  //set memory part 2 (after new columns)
  for (int i = y; i < oldHeight; i++)
  {
    for (int j = 0; j < oldWidth; j++)
    {
      newTileMap[i + count][j] = tileMap[i][j];
      newEntityMap[i + count][j] = entityMap[i][j];
    }
  }

  for (int i = 0; i < oldHeight; i++)
  {
    delete this->tileMap[i];
    delete this->entityMap[i];
  }

  delete[] this->tileMap;
  delete[] this->entityMap;

  this->tileMap = newTileMap;
  this->entityMap = newEntityMap;
}

std::vector<std::string> objFactory::readTextureKey(std::string keyPath)
{
  std::vector<std::string> textures;
  std::string line; 
  std::ifstream is;
  is.open(keyPath);

  if (!is.is_open())
  {
    std::cout << "Failed to open texture key" << std::endl;
    return textures;
  }
  
  //Reads textures from the key file
  textures.clear();
  textures.push_back(std::string("EmptyTile"));
  while (!is.eof())
  {
    std::getline(is, line);
    textures.push_back(line);
  }

  is.close();
  return textures;
}

//This FX is for eventually modifying the current level file's tilemap
void objFactory::modifyLevelTilemap(int newTexture, int x, int y)
{
  std::vector<std::string> lines; 
  std::string line;
  std::ifstream is;
  std::ofstream os;

  is.open("resources/Levels/" + levelName + ".txt");

  if (!is.is_open())
  {
    std::cout << "Failed to open " << "resources/Levels/" + levelName + ".txt" << std::endl;
    return;
  }

  //Loops through the junk
  for (int i = 0; i < 5; ++i)
  {
    std::getline(is, line);
    lines.push_back(line);
  }

  //Loops through the rows we dont care about
  for (int j = 0; j < levelHeight - y; ++j)
  {
    std::getline(is, line);
    lines.push_back(line);
  }

  //Gets the line we care about
  std::getline(is, line);
  //modifies the character
  line[x] = (char)(newTexture + '0');
  lines.push_back(line);

  while (!is.eof())
  {
    std::getline(is, line);
    lines.push_back(line);
  }

  is.close();

  os.open("resources/Levels/" + levelName + ".txt");

  for (std::vector<std::string>::iterator it = lines.begin();
    it != lines.end(); ++it)
  {
    os << *it << std::endl;
  }

  os.close();
}
