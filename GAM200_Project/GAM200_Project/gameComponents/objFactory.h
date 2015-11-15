/*!
 ********************************************************************************
 \file    objFactory.h
 \author  Nolan Taeksang Yoo
 \author  Gabriel Neumann
 \author  Conor Lavelle
 \par     Contact: nolan\@projectexist.net
 \par     Classes: objFactory
 \remarks
 All content © 2015 DigiPen (USA) Corporation, all rights reserved.
 *******************************************************************************/

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

#include "../reactive.h"
#include "../Editor/editable.h"
#include "../Editor/imGuiManager.h"

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory : public ISystem
{
private:
  GOC * createTile(int positionX, int positionY, std::string textureName);
  bool changeTile(char tile, int x, int y);
  bool changeEntity(char entity, int x, int y);
  void insertCol(int x, int count);
  void insertRow(int y, int count);

public:
  std::map<int, GameObjectComposition*> gameObjs;//id, Game object
  //std::vector< const GameObjectComposition*> GetgameObjs();
  void printLevel();
  objFactory();
  GameObjectComposition* makeObject(std::string Name);
  void destroyObject(int killID);
  void destroyAllObjects();
  void objFactory::SerializeAllObjects(Serializer& str);
  // Overloaded methods
  void Initialize();// override;
  void Update(float dt);//override;
  void Shutdown();// override;
  void initializeObjects();
  void loadLevelFrom(std::string fileName);
  void createTiles();
  void SendMessages(Message * message);

  std::vector<std::string> textureKey;
  std::vector<std::string> readTextureKey(std::string levelName);
  void modifyLevelTilemap(int newTexture, int x, int y);

  std::string levelName;
  int levelWidth;
  int levelHeight;
  int ** tileMap;

  bool validPoint(int x, int y);

};
extern objFactory * FACTORY;
extern bool FACTORY_EXISTS;

#endif