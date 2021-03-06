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
#ifdef EDITOR
#include "../Editor/editable.h"
#include "../Editor/imGuiManager.h"
#endif

#ifndef OBJFACTORY_H
#define OBJFACTORY_H

class objFactory : public ISystem
{
private:
  GOC * createTile(int positionX, int positionY, std::string textureName);

  bool changeEntity(char entity, int x, int y);
  void insertCol(int x, int count);
  void insertRow(int y, int count);

public:
  std::map<int, GameObjectComposition*> gameObjs;
  std::map<int, GameObjectComposition*> menuObjs;//id, Game object
  //std::vector< const GameObjectComposition*> GetgameObjs();
  void printLevel();
  objFactory();

  GameObjectComposition* makeObject(std::string Name);
  GameObjectComposition* makeMenuObject(std::string Name);

  void destroyObject(int killID, bool menuObject = false);
  void destroyAllObjects(bool destroyMenus = false);
  void objFactory::SerializeAllObjects(Serializer& str);
  GameObjectComposition* FindObjectByName(std::string name);
  bool loadEntities(std::string entityFile);
  GameComponent* getNewComponent(ComponentTypeId type);
  void addEditorComponents(GOC* object);
  // Overloaded methods
  void Initialize();// override;
  void Update(float dt);//override;
  void Shutdown();// override;
  void initializeObjects();
  void loadLevelFrom(std::string fileName);
  void createTiles();
  void SendMessages(Message * message);

  std::string levelName;
  int levelWidth;
  int levelHeight;
  std::string ** tileMap;

  bool validPoint(int x, int y);

};
extern objFactory * FACTORY;
extern bool FACTORY_EXISTS;

#endif