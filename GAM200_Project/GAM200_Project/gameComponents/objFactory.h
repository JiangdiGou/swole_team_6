//author Nolan Yoo

#include "../Composition.h"
#include <map>
#include "../System.h"
#include "../Utilities.h"
#include "../physicsLib/Transform.h"
#include "../physicsLib/Body.h"

#include "../engineGraphics/Sprite.h"
#include "../engineGraphics/Camera.h"
#include "../engineGraphics/graphicsManager.h"
#include "../WindowsSystem.h"

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory : public ISystem
{
private:
  std::map<int, GameObjectComposition*> gameObjs;//id, Game object

  GOC * createTile(int positionX, int positionY, std::string textureName);
  bool changeTile(char tile, int x, int y);
  bool changeEntity(char entity, int x, int y);
  void insertCol(int x, int count);
  void insertRow(int y, int count);
public:
  void printLevel();
  objFactory();
  GameObjectComposition* makeObject(std::string Name);
  void destroyObject(int killID);
  void destroyAllObjects();
  // Overloaded methods
  void Initialize();// override;
  void Update(float dt);//override;
  void Shutdown();// override;
  void intializeObjects();
  void loadLevelFrom(std::string fileName);
  void createTiles();
  void SendMessages(Message * message);

  std::string fileName;
  std::string levelName;
  int levelWidth;
  int levelHeight;
  char ** tileMap;
  char ** entityMap;

  bool validPoint(int x, int y);

};
extern objFactory * FACTORY;
extern bool FACTORY_EXISTS;

#endif