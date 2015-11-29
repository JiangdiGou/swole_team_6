#include "GameReactive.h"

void GameReactive::Initialize()
{
  fetchTransform();
  //Put stuff here..
}

void GameReactive::Update(float dt)
{
  checkMouseHeld();
  //Put stuff here..
}

void GameReactive::SendMessages(Message* message)
{
  updateMouseFlags(message);
  //...
}

void GameReactive::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
}