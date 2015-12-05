#ifndef COMPONENTTYPEIDS_H
#define COMPONENTTYPEIDS_H
#include "Zilch\BindInternal.hpp"
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
	CT_Body,
	//Max
	CT_TileMapCollision,
	CT_ShapeAAB,
	CT_ShapeLine,

	CT_GameReactive,
	CT_SoundEmitter,

	CT_PlayerTag,
	CT_HUDcomponent,
	CT_Editable,
	CT_MouseVector,
	CT_PlayerState,
	CT_MenuButton,
	CT_OurZilchComponent,
	CT_BadEnemyAI,
  CT_HealthManager,
	CT_PlayerHealthBar,
	CT_PlayerAttack,
	CT_LoadLevel,
  CT_EnemyHealthManager,
  CT_WinLogic,
  CT_TutorialLogic,

  //OK NOW I NEED YOU TO ALWAYS ADD AT END 

  //Hey I noticed you're adding a component type. Can you please add it editorEntityTools.cpp
};
enum ZilchComponentTypeId
{
  CTZ_Example,//0
  CTZ_BasicAIComponent,//1
  CTZ_EndOfGame,//2
  CTZ_EnemyHealthManager,//3
  CTZ_PlayerHealthBar,//4
  CTZ_PlayerHealthManager,//5
  //CTZ_AttackSlash,//6

};
ZilchDeclareExternalBaseType(ComponentTypeId, TypeCopyMode::ReferenceType);
ZilchDeclareExternalBaseType(ZilchComponentTypeId, TypeCopyMode::ReferenceType);

#endif