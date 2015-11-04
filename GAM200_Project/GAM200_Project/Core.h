#ifndef CORE_H
#define CORE_H
#include <vector>
#include "System.h"

class CoreEngine
{
public:
  CoreEngine();
  ~CoreEngine();
  ///Update all the systems until the game is no longer active.
  void GameLoop();
  ///Destroy all systems in reverse order that they were added.
  void DestroySystems();
  ///Broadcasts a message to all systems.
  void BroadcastMessage(Message* m);
  ///Adds a new system to the game.
  void AddSystem(ISystem* system);
  ///Initializes all systems in the game.
  void Initialize();
  unsigned LastTime;
  bool GameActive;

  std::vector<ISystem*> getSystems() const { return Systems; };

private:
  //System Container
  std::vector<ISystem*> Systems;
  //The last time the game was updated


};
class MessageQuit : public Message
{
public:
  MessageQuit() : Message(Mid::Quit) {};
};
//A global pointer to the instance of the 


extern CoreEngine* CORE;
#endif