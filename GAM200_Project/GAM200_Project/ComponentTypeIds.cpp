#include "ComponentTypeIds.h"

ZilchDefineExternalType(ComponentTypeId, "ComponentTypeId", ZLib_Internal, builder, type)
{
  ZilchBindEnum(builder, type, SpecialType::Enumeration);
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_None, "CT_None");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_Transform, "CT_Transform");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_Camera, "CT_Camera");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_Sprite, "CT_Sprite");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_SpriteText, "CT_SpriteText");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_Body, "CT_Body");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_TileMapCollision, "CT_TileMapCollision");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_ShapeAAB, "CT_ShapeAAB");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_ShapeLine, "CT_ShapeLine");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_GameReactive, "CT_GameReactive");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_SoundEmitter, "CT_SoundEmitter");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_PlayerTag, "CT_PlayerTag");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_Editable, "CT_Editable");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_MouseVector, "CT_MouseVector");
  ZilchBindEnumValue(builder, type, ComponentTypeId::CT_PlayerState, "CT_PlayerState");
}
ZilchDefineExternalType(ZilchComponentTypeId, "ZilchCompoentTypeId", ZLib_Internal, builder, type)
{
  ZilchBindEnum(builder, type, SpecialType::Enumeration);
  ZilchBindEnumValue(builder, type, ZilchComponentTypeId::CTZ_Example, "CTZ_Example");
}
