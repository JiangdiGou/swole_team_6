/******************************************************************************/
/*!
\file   GameStateList.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Enum of possible game states
All content � 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef GAME_STATE_LIST_H
#define GAME_STATE_LIST_H

//game state list

enum
{
  //list of all game states 
  GS_GAME = 0,
  GS_LOAD,
  GS_RUN,
  GS_RESTART,
  GS_QUIT,
  GS_NUM
};

#endif // GAME_STATE_LIST_H