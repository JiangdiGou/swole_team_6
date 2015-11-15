#ifndef COMPONENT_H
#define COMPONENT_H
#include "Message.h"
#include "ComponentTypeIds.h"
#include "Serialization\Serialization.h"

class GameObjectComposition;
typedef GameObjectComposition GOC;

class GameComponent
{
public:
friend class GameObjectComposition;

virtual void Initialize() {};
virtual void Update(float dt) {};
virtual void Release() {};
virtual void SendMessages(Message *) {};
virtual void SerializeRead(Serializer& str) {};
virtual void SerializeWrite(Serializer& str) {};

GOC* GetOwner() { return Base; }

ComponentTypeId TypeId;

protected:
virtual ~GameComponent() {};
private:
//pointer to the owner composition
GOC* Base;
};

#endif