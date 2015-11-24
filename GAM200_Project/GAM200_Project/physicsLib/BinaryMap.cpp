/*****************************************************************************/
/*!
\file    BinaryMap.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
The implementation for the Binary Map, probably not going to be use for now.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

//#include "Precompiled.h"
#include "BinaryMap.h"
//#include "../GameComponents/objFactory.h"
//Collision flags
#define	COLLISION_LEFT		0x00000001	//0001
#define	COLLISION_RIGHT		0x00000002	//0010
#define	COLLISION_TOP		0x00000004	//0100
#define	COLLISION_BOTTOM	0x00000008	//1000

#define TILE_WIDTH 2.0f
#define HALF_TILE_WIDTH 1.0f
#define QUARTER_TILE_WIDTH 0.5f
#define THIRD_TILE_WIDTH 0.33f
#define EIGHTH_TILE_WIDTH 0.25f

#define CEILING_TILE 2
#define HOPPABLE_PLATFORM 9
#define SPIKE '_'
#define BLOCKONE 
#define BLOCKTWO

//Gethas->???

TileMapCollision::TileMapCollision()
{
  
}

void TileMapCollision::Initialize() 
{
	transform_ = reinterpret_cast<Transform *>(GetOwner()->GetComponent(CT_Transform));
	rigid_ = reinterpret_cast<Body *>(GetOwner()->GetComponent(CT_Body));
	//tileMap = FACTORY->tileMap;
	mapWidth = &FACTORY->levelWidth;
	mapHeight = &FACTORY->levelHeight;
	int* mapHeight;
	//owner->GetComponent(CT_Body)
	//Where do I add the component so it gets updated?
	//pos_ = transform_->GetPosition();
}

//Last thing to change: Edge cases from player hitting the corner of a tile head-on
void TileMapCollision::Update(float dt)
{
	Vector3 pos_ = transform_->GetPosition();
	Vector2 vel_ = rigid_->Velocity;
	Vector2 acc_ = rigid_->Acceleration;
  int gridCollisionflag_ = CheckBinaryMapCollision(pos_.x + HALF_TILE_WIDTH, pos_.y + HALF_TILE_WIDTH);
  //rigid_->tx = GetOwner()->has(Transform);
  if (gridCollisionflag_ & COLLISION_TOP) //too tired to think about why this is happening, split into four if-statements and adjusted
  {
	  SnapToCellY(pos_.y, rigid_->bodyTrans->GetPositionXY().y);
    pos_.y -= HALF_TILE_WIDTH;
	rigid_->Position.y = pos_.y;
    if (vel_.y > 0)
      vel_.y = 0;
    if (acc_.y > 0)
      acc_.y = 0;
    
  }
  if (gridCollisionflag_ & COLLISION_BOTTOM )
  {
	  SnapToCellY(pos_.y, rigid_->bodyTrans->GetPositionXY().y);
    if (vel_.y < 0)
      vel_.y = 0;
	  if (acc_.y < 0)
		acc_.y = 0;
  }
  if (gridCollisionflag_ & COLLISION_LEFT)
  {
	  SnapToCellX(pos_.x, rigid_->bodyTrans->GetPositionXY().x);
    if (vel_.x < 0)
      vel_.x = 0;
    if (acc_.x < 0)
      acc_.x = 0;
  }
  if (gridCollisionflag_ & COLLISION_RIGHT)
  {
	  SnapToCellX(pos_.x, rigid_->bodyTrans->GetPositionXY().x);
    if (vel_.x > 0)
      vel_.x = 0;
    if (acc_.x > 0)
      acc_.x = 0;
  }
}
void TileMapCollision::Release()
{

}


//I split these up trying to find a bug but it was something unrelated
void TileMapCollision::SnapToCellX(float transfcoord, float rigidcoord)
{
  transfcoord = static_cast<int>(transfcoord) + QUARTER_TILE_WIDTH;
  rigidcoord = transfcoord;
}
void TileMapCollision::SnapToCellY(float transfcoord, float rigidcoord)
{
  //Snapping the coordinate to the center of its location
  //(cells are 1 wide)
  //transform is at the bottom-left of the sprite
  transfcoord = static_cast<int>(transfcoord) + HALF_TILE_WIDTH;
  rigidcoord = transfcoord;
}



int TileMapCollision::GetCellValue(int fx, int fy)
{
  //Divide by 2 (since all values are * tile width (which is 2.0f)
  fx /= 2;
  fy /= 2;
  int x = static_cast<int>(fx);
  int y = static_cast<int>(fy);

  //Preventing access outside of the array.
  //(aka what happens when/if we go beyond the map)
  if (x >= *mapWidth-1 || y >= *mapHeight-1
    || x < 0 || y < 0)
  {
    return 0;
  }
  //Array checks from the top-right, ugh
  //return (*(tilemap_.tiles))[(y * tilemap_.width) + x];
  //return (*(tilemap_.tiles))[tilemap_.numTiles - (tilemap_.width * y) - (tilemap_.width - x + 1)];
  //int index = tilemap_.numTiles - 1 - (tilemap_.width * (tilemap_.height - 1 - y)) - (tilemap_.width - 1 - x);
  //int index = tileMap.numTiles - 1 - (tileMap.width - 1) + x - (tileMap.width * y);
  //return (*(tilemap_.tiles))[index];
  return tileMap[fx][fy]-48;
}


int TileMapCollision::CheckBinaryMapCollision(float PosX, float PosY)
{
  //Creating the flag_ to be bit-shifted
  flag_ = 0;
  //Preventing repeat calculations
  //float HALF_TILE_WIDTH = scaleX / 2.0f, HALF_TILE_WIDTH = scaleY / 2.0f,
    //QUARTER_TILE_WIDTH = scaleX / 4.0f, QUARTER_TILE_WIDTH = scaleY / 4.0f;

  /*********************************************
     t1    t2
  l1           r1
  l2           r2    CREATING THE HOT SPOTS
     b1    b2
  **********************************************/
  /*
  left1X = PosX - HALF_TILE_WIDTH;
  left1Y = PosY + QUARTER_TILE_WIDTH;
  left2X = left1X;
  left2Y = PosY - QUARTER_TILE_WIDTH;

  top1X = PosX - QUARTER_TILE_WIDTH;
  top1Y = PosY + HALF_TILE_WIDTH;
  top2X = PosX + QUARTER_TILE_WIDTH;
  top2Y = top1Y;

  right1X = PosX + HALF_TILE_WIDTH;
  right1Y = left1Y;
  right2X = right1X;
  right2Y = left2Y;

  bot1X = top1X;
  bot1Y = PosY - HALF_TILE_WIDTH;
  bot2X = top2X;
  bot2Y = bot1Y;
  */

  //@ Maybe check top/bottom first, then left/right?
  //This would keep long falls from "snapping" left/right at the bottom
  //And you're pretty much never gonna go super-fast to the left or right
  //Try it later.


  //Here we compare the values from GetCellValue, which are the IDs of the tiles
  //So, 0 == empty, 1 == wall, 2 == ceiling, etc...
  int checkID1, checkID2;

  /* Left*/
  checkID1 = GetCellValue(PosX - QUARTER_TILE_WIDTH, PosY + HALF_TILE_WIDTH - 0.20f);
  checkID2 = GetCellValue(PosX - QUARTER_TILE_WIDTH, PosY - HALF_TILE_WIDTH + 0.20f);
  if (checkID1 || checkID2)
  {
	  if (checkID1 != HOPPABLE_PLATFORM && checkID2 != HOPPABLE_PLATFORM)
	  {
		  flag_ = flag_ | COLLISION_LEFT;
//		  if (checkID1 == SPIKE || checkID2 == SPIKE)

	  }
  }
  /* Right */
  checkID1 = GetCellValue(PosX + QUARTER_TILE_WIDTH, PosY + HALF_TILE_WIDTH - 0.20f);
  checkID2 = GetCellValue(PosX + QUARTER_TILE_WIDTH, PosY - HALF_TILE_WIDTH + 0.20f);
  if (checkID1 || checkID2)
  {
    if (checkID1 != HOPPABLE_PLATFORM && checkID2 != HOPPABLE_PLATFORM)
      flag_ = flag_ | COLLISION_RIGHT;
  }

  /* Top */
  checkID1 = GetCellValue(PosX - EIGHTH_TILE_WIDTH + .20f, PosY + HALF_TILE_WIDTH);
  checkID2 = GetCellValue(PosX + EIGHTH_TILE_WIDTH - .20f, PosY + HALF_TILE_WIDTH);
  if (checkID1 || checkID2)
  {
    if (checkID1 != HOPPABLE_PLATFORM && checkID2 != HOPPABLE_PLATFORM)
      flag_ = flag_ | COLLISION_TOP;
  }

  /* Bottom */
  checkID1 = GetCellValue(PosX - EIGHTH_TILE_WIDTH + .20f, PosY - HALF_TILE_WIDTH);
  checkID2 = GetCellValue(PosX + EIGHTH_TILE_WIDTH - .20f, PosY - HALF_TILE_WIDTH);
  if (checkID1 || checkID2)
  {
    //Check whether we should actually do downwards collision
    //(If we're entirely on a platform, and not currently jumping above it.)
    if (checkID1 == HOPPABLE_PLATFORM && checkID2 == HOPPABLE_PLATFORM)
    {
      //Case 1: Upward velocity? Do nothing
      //Case 2: Downward velocity, player is in middle of platform, do nothing
      //Case 3: Downward velocity, player is comfortably above middle of platform, do something!
		if (rigid_->Velocity.y < 0)
      {
        //If our "feet" are touching the top half of the tile, and if they're touching it JUST BARELY
			if (static_cast<int>(rigid_->bodyTrans->GetPositionXY().y) % 2 == 1)
				if (rigid_->bodyTrans->GetPositionXY().y - static_cast<float>(static_cast<int>(rigid_->bodyTrans->GetPositionXY().y)) > .95f)
            flag_ = flag_ | COLLISION_BOTTOM;
      }

      //Need to account for when one half of us is on a hoppable platform and the other half is in midair or on another thing
    }
    else
    {
      flag_ = flag_ | COLLISION_BOTTOM;
    }
  }

  //At the end of this function, "flag_" will be used to determine which sides
  //of the object instance are colliding. 2 hot spots will be placed on each side.
  return flag_;

}

bool TileMapCollision::TopIsColliding()
{
	//if (flag_ && "")


  return (flag_ & COLLISION_TOP) != 0;
}
bool TileMapCollision::BottomIsColliding()
{

  return (flag_ & COLLISION_BOTTOM) != 0;
}
bool TileMapCollision::LeftIsColliding()
{
  return (flag_ & COLLISION_LEFT) != 0;
}
bool TileMapCollision::RightIsColliding()
{
  return (flag_ & COLLISION_RIGHT) != 0;
}