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
#include "../Serialization/TextSerialization.h"


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

GameObjectComposition* objFactory::makeMenuObject(std::string Name)
{
  GameObjectComposition *toReturn = new GameObjectComposition();

  toReturn->ObjectName = Name;
  toReturn->ObjectId = nextID;
  menuObjs[nextID] = toReturn;
  nextID++;
  return toReturn;
}

void objFactory::destroyObject(int killID, bool menuObject)
{
  if (menuObject)
  {
    if (menuObjs[killID] == NULL)
    {
      /* assert that we should never try to destroy an object
      that doesn't exist */
      throw AssertionError(std::string("Object ID " + std::to_string(killID)
        + " is not destroyable."
        ));
    }
    else
    {
      menuObjs.at(killID)->~GameObjectComposition();
      menuObjs.erase(killID);
    }
  }
  else
  {
    if (gameObjs[killID] == NULL)
    {
      /* assert that we should never try to destroy an object
         that doesn't exist */
      throw AssertionError(std::string("Object ID " + std::to_string(killID)
        + " is not destroyable."
        ));
    }
    else
    {
      gameObjs.at(killID)->~GameObjectComposition();
      gameObjs.erase(killID);
    }
  }
}

void objFactory::destroyAllObjects(bool DestroyMenus)
{
  std::map<int, GameObjectComposition*>::iterator it;
  for (it = gameObjs.begin(); gameObjs.size() > 0; it = gameObjs.begin())
  {
    destroyObject(it->first);
  }

  if (DestroyMenus)
  {
    for (it = menuObjs.begin(); menuObjs.size() > 0; it = menuObjs.begin())
    {
      destroyObject(it->first, true);
    }

    menuObjs.clear();
  }

  gameObjs.clear();
}
void objFactory::SerializeAllObjects(Serializer& str)
{
  std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
  for (; it != gameObjs.end(); ++it)
  {
    //We dont want to serialize this at this second, might fix later, but these 
    //Two will eventually need to be handled specially, leaving hardcoded in gamelogic for now.

    if (it->second->GetName() == std::string("GAMECAMERA")
      || it->second->GetName() == std::string("GAMEPLAYER"))
    {
      continue;
    }
    else
    {
      //Another check, whether or not tile
      Editable* pEditable = it->second->has(Editable);

      //Also, we need to not serialize tiles or we'll spawn them twice. 
      if (pEditable && pEditable->isATile())
        continue;
      else
        it->second->SerializeWrite(str);

    }
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
  if (!(CORE->Pause))
  {
    std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
    for (; it != gameObjs.end(); ++it)
    {
      it->second->Update(dt);
    }
  }
  else
  {
    std::map<int, GameObjectComposition*>::iterator it = menuObjs.begin();
    for (; it != menuObjs.end(); ++it)
    {
      it->second->Update(dt);
    }
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
    if (!(CORE->Pause))
    {
      //MessageCharacterKey* messageChar = (MessageCharacterKey*)message;
      std::map<int, GameObjectComposition*>::iterator it = gameObjs.begin();
      for (; it != gameObjs.end(); ++it)
      {
        it->second->SendMessages(message);
      }
    }
    else
    {
      std::map<int, GameObjectComposition*>::iterator it = menuObjs.begin();
      for (; it != menuObjs.end(); ++it)
      {
        it->second->SendMessages(message);
      }
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

  //Don't want the empty tile to have collision, NC thing should allow tiles with no collision
  if (!(textureName == "E" ||  getTildePrefix(textureName) == std::string("NC")))
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

bool objFactory::loadEntities(std::string entityFile)
{
  Framework::TextSerializer serializer;
  char* line = new char[256];
  int type;
  std::vector<int> previousTypes;
  bool newComposition = false;

  if (!(serializer.Open(entityFile)))
    return false;

  bool firstCreated = false;
  GOC* currentEntity = NULL;
  while (!(serializer.stream.eof()))
  {
    //Gets type info
    serializer.stream.getline(line, 256);
    if (serializer.stream.eof())
      break;

    //std::cout << "Line: " <<  line << std::endl;

    if (line[0] == '#')
    {
      serializer.stream.getline(line, 256);
      currentEntity = makeObject(line);
      addEditorComponents(currentEntity);
    }
    //It's sometimes getting an empty line?
    else
    {
      try
      {
        type = std::stoi(line);
      }
      catch (std::invalid_argument)
      {
        continue;
      }
      std::cout << "Line: " <<  line << std::endl;
      //printf("||%c||", line);
    
      //Creates component
      GameComponent* comp = getNewComponent((ComponentTypeId)type);
      //Add comp
      std::cout << "Adding new Comp: " << type << std::endl;
      currentEntity->AddComponent((ComponentTypeId)type, comp);
      //Add comp to types vect
      //previousTypes.push_back(type);
      //Set Comp
      comp->SerializeRead(serializer);
    }

    //  try
    //  {
    //    type = std::stoi(line);
    //  }
    //  catch (std::invalid_argument)
    //  {
    //    continue;
    //  }
    ////Makes first component if its needs to
    //if (!firstCreated)
    //{
    //  currentEntity = makeObject("We don't save names.");
    //  firstCreated = true;
    //}

    ////Checks whether this component already exists on object 
    //for (std::vector<int>::iterator it = previousTypes.begin();
    //  it != previousTypes.end(); ++it)
    //{
    //  //If this type already exists in vect, make a new comp
    //  if (*it == type)
    //  {
    //    newComposition = true;
    //    break;
    //  }
    //  else
    //    newComposition = false;
    //}

    ////Creates component
    //GameComponent* comp = getNewComponent((ComponentTypeId)type);
    ////If it should make a new composition
    //if (newComposition)
    //{
    //  std::cout << "Adding new Composition" << std::endl;
    //  //Reset flag
    //  newComposition = false;
    //  //Clear types vect
    //  previousTypes.clear();
    //  //Add Editor components if they don't already exist
    //  addEditorComponents(currentEntity);
    //  //Make obj
    //  currentEntity = makeObject("No names");
    //  //Add comp
    //  std::cout << "Adding new Comp: " << type << std::endl;
    //  currentEntity->AddComponent((ComponentTypeId)type, comp);
    //  //Add comp to types vect
    //  previousTypes.push_back(type);
    //  //Set Comp
    //  comp->SerializeRead(serializer);
    //}
    //else
    //{
    //  //Add comp
    //  std::cout << "Adding new Comp: " << type << std::endl;
    //  currentEntity->AddComponent((ComponentTypeId)type, comp);
    //  //Add comp to types vect
    //  previousTypes.push_back(type);
    //  //Set Comp
    //  comp->SerializeRead(serializer);
    //}
  }

  if (currentEntity)
    addEditorComponents(currentEntity);

  //Breaks in this fx
  initializeObjects();
  delete [] line;
  
}

void objFactory::addEditorComponents(GOC* object)
{
#ifdef EDITOR
  Editable* editable = new Editable(false);
  object->AddComponent(CT_Editable, editable);
#endif
}

GameComponent* objFactory::getNewComponent(ComponentTypeId type)
{
  switch (type)
  {
  case CT_Transform:
    return new Transform();

  case CT_Camera:
    return new Camera();

  case CT_Sprite:
    return new Sprite();

  case CT_SpriteText:
    return new SpriteText(std::string("default text"));

  case CT_Body:
    return new Body();

  case CT_TileMapCollision:
    return new TileMapCollision();

  case CT_ShapeAAB:
    return new ShapeAAB();

  case CT_ShapeLine:
    return new ShapeLine();

  case CT_GameReactive:
    return new GameReactive();

  case CT_SoundEmitter:
    return new SoundEmitter();

  case CT_PlayerTag:
	  return new PlayerTag();

  case CT_HUDcomponent:
	  return new HUDcomponent();

  case CT_Editable:
    return new Editable();

  case CT_MouseVector:
    return new MouseVector();

  case CT_PlayerState:
    return new PlayerState();

  case CT_MenuButton:
    return new MenuButton(RESUME);

  default:
    return NULL;
  }
}