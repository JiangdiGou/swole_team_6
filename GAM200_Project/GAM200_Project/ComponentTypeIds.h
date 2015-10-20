#ifndef COMPONENTTYPEIDS_H
#define COMPONENTTYPEIDS_H
//enum containing ComponentTypeIds
enum ComponentTypeId
{
	//Invalid component id
	CT_None = 0,
	//Basic Components
	CT_Transform,
	//Graphics
	CT_Camera,
	CT_Sprite,
  CT_SpriteText,
	//Physics
	CT_RigidBody,
	CT_AABB,
	CT_Circle,
	//Max
	CT_MaxComponents,
	CT_CircleCollider,
	CT_BoxCollider,
	CT_TileMapCollider,
	CT_Player_Controller,
	CT_MOVEPLATFORM,
	CT_DESTROY,
	CT_SPAWNBLOCK,
	CT_PLAYERDEATH,
	
};
#endif