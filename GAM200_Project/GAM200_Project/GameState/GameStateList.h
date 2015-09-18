/******************************************************************************/
/*!
\file   GameStateList.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Enum of possible game states
*/
/******************************************************************************/

#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

//game state list

enum
{
  //list of all game states 
  GS_GAME = 0,
  GS_RESTART,
  GS_QUIT,
  GS_NUM
};

#endif // GAME_STATE_LIST_H