/******************************************************************************/
/*!
\file   Component.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Declartions for GameComponent
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef COMPONENT_H
#define COMPONENT_H
#include "Message.h"
#include "ComponentTypeIds.h"
#include "Serialization\Serialization.h"
#include "Zilch\Zilch.hpp"
#include "Zilch\BindInternal.hpp"

using namespace Zilch;

class GameObjectComposition;

class GameComponent : public IZilchObject
{
public:
ZilchDeclareBaseType(GameComponent, TypeCopyMode::ReferenceType);
friend class GameObjectComposition;

virtual void Initialize() {};
virtual void Update(float dt) {};
virtual void Release() {};
virtual void SendMessages(Message *) {};
virtual void SerializeRead(Serializer& str) {};
virtual void SerializeWrite(Serializer& str) {};

GameObjectComposition* GetOwner() { return Base; }
ComponentTypeId TypeId;
virtual ~GameComponent() {};

protected:
private:
//pointer to the owner composition
GameObjectComposition* Base;
};

#endif