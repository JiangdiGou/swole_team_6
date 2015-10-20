//author Nolan Yoo

#include "objFactory.h"
#include <random>

#include "../AssertionError/AssertionError.h"
#include "../WindowsSystem.h"
bool FACTORY_EXISTS;
objFactory::objFactory()
{
  FACTORY = this;
  FACTORY_EXISTS = true;
}

GameObjectComposition* objFactory::makeObject(std::string Name)
{
  GameObjectComposition *toReturn = new GameObjectComposition();

  std::mt19937 init_generator;//Mersenne Twister 19937 generator
  init_generator.seed(std::random_device()());
  std::uniform_int_distribution<std::mt19937::result_type> idgen(1, 2147483647);

  int gen = idgen(init_generator);

  while (gameObjs[gen] != NULL)
  {
    //already using gen
    gen = idgen(init_generator);
  }

  toReturn->ObjectId = gen;
  gameObjs[gen] = toReturn;
  return toReturn;
}

void objFactory::destroyObject(int killID)
{
  if (gameObjs[killID] == NULL)
  {
    //already using gen
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
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    destroyObject(it->first);
  }

  gameObjs.clear();
}
// Overloaded methods
void objFactory::Initialize()
{

}
void objFactory::Update(float dt)
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    it->second->Update();
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
    garbage = getLineFromFile(5 + i + 2, fileName);
    std::copy(garbage.begin(), garbage.end(), tileMap[i]);
  }

  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 1 + 2 + arrayY, fileName);
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
      switch (tileMap[i][j])
      {
      case '1':
        createTile(j - levelWidth/2,levelHeight/2-i, std::string("Smiley2"));
        break;
      case '2':
        createTile(j - levelWidth / 2, levelHeight / 2 - i, std::string("Smiley3"));
        break;
      }
    }
  }
}

GOC * objFactory::createTile(int positionX, int positionY, std::string textureName)
{
  GOC * newTile = FACTORY->makeObject("newTile");
  Transform * tileTransform = new Transform();
  tileTransform->SetPosition(positionX, positionY, 0);
  Sprite * tileSprite = new Sprite();
  tileSprite->texture = graphics->spriteAtlas.textures[textureName];//TileAtlas
  newTile->AddComponent(CT_Transform, tileTransform);
  newTile->AddComponent(CT_Sprite, tileSprite);

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