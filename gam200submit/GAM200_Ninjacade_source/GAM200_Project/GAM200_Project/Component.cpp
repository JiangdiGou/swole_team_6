/******************************************************************************/
/*!
\file   Component.cpp
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Zilch Binding for Game Component
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "Component.h"
#include "Composition.h"

ZilchDefineType(GameComponent, "GameComponent", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  //ZilchBindConstructor(builder, type, GameComponent, ZilchNoNames);
  //ZilchBindDestructor(builder, type, GameComponent);

  ZilchBindMethod(builder, type, &GameComponent::GetOwner, ZilchNoOverload, "GetOwner", ZilchNoNames);
  ZilchBindMethod(builder, type, &GameComponent::Initialize, ZilchNoOverload, "Initialize", ZilchNoNames);
  ZilchBindMethod(builder, type, &GameComponent::Update, ZilchNoOverload, "Update", ZilchNoNames);
  ZilchBindMethod(builder, type, &GameComponent::Release, ZilchNoOverload, "Release", ZilchNoNames);
  //ZilchBindMethod(builder, type, &GameComponent::SendMessages, ZilchNoOverload, "SendMessages", ZilchNoNames);
  //ZilchBindMethod(builder, type, &GameComponent::SerializeRead, ZilchNoOverload, "SerializeRead", ZilchNoNames);
  //ZilchBindMethod(builder, type, &GameComponent::SerializeWrite, ZilchNoOverload, "SerializeWrite", ZilchNoNames);

  ZilchBindField(builder, type, &GameComponent::TypeId, "TypeId", PropertyBinding::GetSet);
}