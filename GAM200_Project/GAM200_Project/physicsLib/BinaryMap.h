//
//#include "../Composition.h"
//#include "../GameComponents/objFactory.h"
//#include "Transform.h"
//#include "math_utility.h"
//#include "Body.h"
//#include "../gameLevel.h"
//
//class TileMapCollision : public GameComponent
//{
//public:
//	TileMapCollision();//gameLevel::TileMapData &tilemap);//, gameLevel::);//objFactory::TileMapData &tilemap);
//  friend RigidBody;
//  void Initialize() override;
//  void Update(float dt) ;
//  void Release() override;
//  Transform* TransTile = GetOwner()->has(Transform);
//  Transform* TransBody = GetOwner()->has(Transform);
//  //Returns the tilemap ID of the object, and sets reference to the object if it hit something.
//  /*int GetCurrentGameObject(GameObject &ref);*/
//  bool TopIsColliding();
//  bool BottomIsColliding();
//  bool LeftIsColliding();
//  bool RightIsColliding();
//  
//private:
////  TileMapCollision();
//
//  int flag_; //Our collision flag
//
//  //In our owner's Transform:
//  Transform &transform_;
//  Vector3 &pos_;
//  //In our owner's RigidBody:
//  RigidBody &rigid_;
//  Vector2 &vel_;
//  Vector2 &acc_;
//
//  char** tileMap;
//  int* mapWidth;
//  int* mapHeight;
//  GameObjectComposition* currentTile;
//
//  //Valid reference as long as FactoryManager is alive,
//  //and TileMapCollision is only alive while FactoryManager is.
//  //gameLevel::TileMapData &tilemap_;
//  
//  //How do we get info to our owner? We need to communicate our flags to them.
//  //iscollidingup/down/left/right
//  
//  //Transform we can just edit here
//
//  //Helper functions:
//  int CheckBinaryMapCollision(float posX, float posY); //returns our collision flags
//  void SnapToCellX(float &transfcoord, float &rigidcoord); //Given a float value, snaps left 1/4 tile away from a wall
//  void SnapToCellY(float &transfcoord, float &rigidcoord); //Given a float value, snaps to nearest int (i.e. border of tile)
//  int GetCellValue(int fx, int fy);
//
//};