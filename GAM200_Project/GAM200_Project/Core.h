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
  ///Adds a new system to the game.
  void AddSystem(ISystem* system);
  ///Initializes all systems in the game.
  void Initialize();
private:
  //System Container
  std::vector<ISystem*> Systems;
  //The last time the game was updated
  unsigned LastTime;
  bool GameActive;
};
#endif