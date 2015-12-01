#include "GameReactive.h"

void GameReactive::Initialize()
{
  fetchTransform();
  //Put stuff here..
}

void GameReactive::Update(float dt)
{
  if (!active)
  {
    setDefaultOverride();
    return;
  }

  checkMouseHeld();
  //Put stuff here..
}

void GameReactive::SendMessages(Message* message)
{
  if (!active)
  {
    setDefaultOverride();
    return;
  }

  updateMouseFlags(message);
  //...
}

void GameReactive::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
}


ZilchDefineType(GameReactive, "GameReactive", ZLib_Internal, builder, type)
{

}