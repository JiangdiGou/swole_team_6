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
class OurZilchComponent;

//Vector of components, used for storage of components
typedef std::vector<GameComponent*> ComponentArray;
typedef std::vector<GameComponent*> ZilchComponentArray;



class GameObjectComposition : public IZilchObject
{
public:
ZilchDeclareBaseType(GameObjectComposition, TypeCopyMode::ReferenceType);
friend class objFactory;

GameComponent* GetZilchComponent(ZilchComponentTypeId typeId) const;
GameComponent* GetComponent(ComponentTypeId typeId) const;
//Transform * GetTransform() const;
//Stupid AF functions
GameObjectComposition* FindObject(std::string name);
float ourCos(float angle);
float ourSin(float angle);
float ourTan(float angle);
float ourACos(float angle);
float ourASin(float angle);
float ourATan(float angle);
float zDistanceSq(Vector3 pos1, Vector3 pos2);
float zSqrt(float val);
void CastRay(Vec2D pos1, Vec2D pos2);
GameObjectComposition* GetRayResult(int index);
GameComponent * GameObjectComposition::ZilchGetComponent(std::string name) const;
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
std::string GetName();

//A group of actions
ActionGroup Actions;
bool MarkedForDeath = false;
//FACTORY ONLY: Use CreateEmptyComposition on factory instead
GameObjectComposition();
//FACTORY ONLY: Use Destroy instead, factory will call the destructor correctly
~GameObjectComposition();
private:

std::vector <GameObjectComposition*> objsInRay;
//Sorted array of components.
ComponentArray Components;
typedef ComponentArray::iterator ComponentIt;
ZilchComponentArray ZilchComponents;

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
