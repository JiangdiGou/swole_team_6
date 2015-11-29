#ifndef GAMEREACTIVE_H
#define GAMEREACTIVE_H

//This is the interface  for the editor into components.

#include "../Component.h"
#include "../reactive.h"

class GameReactive : public Reactive
{
public:
  void Initialize() override;
  void Update(float dt) override;
  void SendMessages(Message* message) override;

  void SerializeWrite(Serializer& str);


private:
  int stuff;

};

#endif