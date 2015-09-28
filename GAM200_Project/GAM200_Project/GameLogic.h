#include <string>
#include "System.h"
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
class GameLogic : public ISystem
{
public:
  GameLogic();
  ~GameLogic();
  void Initialize();
  void Update(float timeslice);
  virtual std::string GetName() { return "GameLogic"; }
  void LoadLevelFile(const std::string& file);
  unsigned GrabbedObjectId;
};
//A global pointer to our game so that it can be accessed from anywhere.
extern GameLogic* LOGIC;
#endif