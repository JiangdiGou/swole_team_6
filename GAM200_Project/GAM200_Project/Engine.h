/******************************************************************************/
/*!
\file   Engine.h
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
Header for libraries and engine includes
*/
/******************************************************************************/
#ifndef ENGINE_H
#define ENGINE_H

// ---------------------------------------------------------------------------

//Libraries
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <windows.h>

//Engine Includes

#include "engineGraphics\Graphics.h"
#include "Composition.h"
#include "./physicsLib/Transform.h"
#include "./gameComponents/objFactory.h"
#include "./engineAudio/Sound.h"
#include "./engineAudio/SoundEmitter.h"
#include "System.h"
#include "Core.h"
#include "./physicsLib/PhysicsManager.h"

#endif