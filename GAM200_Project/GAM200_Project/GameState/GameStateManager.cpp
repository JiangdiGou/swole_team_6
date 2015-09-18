/******************************************************************************/
/*!
\file   GameStateManager.c
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Game State Manager, sets up initial game state and updates game state based
upon current state
*/
/******************************************************************************/

#include "GameStateManager.h"
#include "GameState_Default.h"

// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void(*GameStateLoad)() = 0;
void(*GameStateInit)() = 0;
void(*GameStateUpdate)() = 0;
void(*GameStateDraw)() = 0;
void(*GameStateFree)() = 0;
void(*GameStateUnload)() = 0;

void GameStateMgrInit(unsigned int gameStateInit)
{
  // set to initial
  gGameStateInit = gameStateInit;

  // reset the other states
  gGameStateCurr =
    gGameStatePrev =
    gGameStateNext = gGameStateInit;

  // call the update to set the function pointers
  GameStateMgrUpdate();
}

void GameStateMgrUpdate()
{
  if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
    return;

  switch (gGameStateCurr)
  {
  case GS_GAME:
    GameStateLoad = GameStateDefaultLoad;
    GameStateInit = GameStateDefaultInit;
    GameStateUpdate = GameStateDefaultUpdate;
    GameStateDraw = GameStateDefaultDraw;
    GameStateFree = GameStateDefaultFree;
    GameStateUnload = GameStateDefaultUnload;
    break;

  }
}