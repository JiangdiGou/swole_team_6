#ifndef COMPOSITION_H
#define COMPOSITION_H
#include "Component.h"
#include "ComponentTypeIds.h"
#include "PleaseWork/ActionSystem.h"
//#include "gameComponents/objFactory.h"
#include <vector>//TO BE MOVED - container header

using namespace ActionSystem;
//Game object ID type
typedef unsigned int GOCId;

//Vector of components, used for storage of components
typedef std::vector<GameComponent*> ComponentArray;

class GameObjectComposition : public IZilchObject
{
public:
ZilchDeclareBaseType(GameObjectComposition, TypeCopyMode::ReferenceType);
friend class objFactory;

GameComponent* GetComponent(ComponentTypeId typeId) const;
//Transform * GetTransform() const;

///Message interface See Message.h
///Message will be sent to each component on this composition.
void SendMessages(Message* message);

///Type safe way of accessing components.
template<typename type>
type* GetComponentType(ComponentTypeId typeId);

void Initialize();

void Update(float dt);

void SerializeRead(Serializer& str);
void SerializeWrite(Serializer& str);

void Destroy();

bool RemoveComponent(ComponentTypeId typeId, GameComponent* toBeRemoved);
void AddComponent(ComponentTypeId typeId, GameComponent* component);
//ActiongGroup Actions;
//Game Obj's Id
GOCId GetId() { return ObjectId; }

//Game Obj's Name
std::string GetName() { return ObjectName; }

//A group of actions
ActionGroup Actions;

//FACTORY ONLY: Use CreateEmptyComposition on factory instead
GameObjectComposition();
//FACTORY ONLY: Use Destroy instead, factory will call the destructor correctly
~GameObjectComposition();
private:

//Sorted array of components.
ComponentArray Components;
typedef ComponentArray::iterator ComponentIt;

//A unique id for each object used to safely reference 
//GOCs.
GOCId ObjectId;

//We need to do some things by name eventually.
std::string ObjectName;

//The constructor and destructor are private to prevent a user
//from creating or deleting an object directly they must use the Destroy function


};

typedef GameObjectComposition GOC;

//type safe way of accessing components
//Transform* transform = object->has(Transform);
template<typename type>
type * GameObjectComposition::GetComponentType(ComponentTypeId typeId)
{
return static_cast<type*>(GetComponent(typeId));
}

#define has(type) GetComponentType<type>(CT_##type);
#endif
