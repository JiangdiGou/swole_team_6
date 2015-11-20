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
	CT_Body,
  //Max
	CT_TileMapCollision,
	CT_ShapeAAB,
	CT_ShapeLine,

	CT_Reactive,
	CT_SoundEmitter,

	CT_TestComponent,

  //INSERT NEW COMPONENTS HERE TILL I FIGURE OUT THE MOUSEVECTOR AND PLAYERSTATE BUG

  CT_Editable,
  CT_MouseVector,
  CT_PlayerState
//Hey I noticed you're adding a component type. Can you please add it to editorEntityTools.cpp's
//Get componennt name and createComponentPointer, which are just hard coded switches
};

#endif