/******************************************************************************/
/*!
\file   GameLogic.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
GameLogic System for our engine, used to create levels, calls objFactory
All content � 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <string>
#include "../System.h"
#include "../Composition.h"
#include "../engineGraphics/Texture.h"
class GameLogic : public ISystem
{
public:
  GameLogic();
  ~GameLogic();
  void Initialize();
  void Update(float timeslice);
  virtual std::string GetName() { return "GameLogic"; }
  virtual void SendMessages(Message *);
  void LoadLevelFile(const std::string& file);
  unsigned GrabbedObjectId;
  void createLevel(std::string levelPath);

  GOC* player = NULL;
  GOC* player2 = NULL; 
  Texture* textureRunBlue = NULL;
  Texture* textureIdleBlue = NULL;
};
//A global pointer to our game so that it can be accessed from anywhere.
extern GameLogic* LOGIC;
#endif