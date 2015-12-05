/******************************************************************************/
/*!
\file   GameStateManager.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Game State Manager declarations
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef GAME_STATE_MANAGER_H
#define GAME_STATE_MANAGER_H

#include "GameStateList.h"

extern unsigned int gGameStateInit;
extern unsigned int gGameStateCurr;
extern unsigned int gGameStatePrev;
extern unsigned int gGameStateNext;

extern void(*GameStateLoad)();
extern void(*GameStateInit)();
extern void(*GameStateUpdate)();
extern void(*GameStateDraw)();
extern void(*GameStateFree)();
extern void(*GameStateUnload)();

// Manager Intialization
void GameStateMgrInit(unsigned int gameStateInit);

// Updates function pointers
void GameStateMgrUpdate();

#endif // GAME_STATE_MGR_H