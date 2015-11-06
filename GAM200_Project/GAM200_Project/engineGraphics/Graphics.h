/*****************************************************************************/
/*!
\file       Graphics.h
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     [A[BStores information that almost all graphics systems need
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
	#pragma comment(lib, "graphicsLibsWin/glew32s.lib")
	#pragma comment(lib, "graphicsLibsWin/SOIL.lib")
	#pragma comment(lib, "./OpenGL32.Lib" )
#endif

//Core Graphics Functionality 
#define GLEW_STATIC
#include "glew/glew.h"
#include "glew/wglew.h"

//Math
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//Printing out stuff
#include<iostream>
#include "../logger/logger.h"
#include <vector>
#include <string>
#include "../physicsLib/math_utility.h"

void setupPixelFormatDescriptor(HDC handleDeviceContext);

//#define GFXLOG

#ifdef GFXLOG
#define WARNINGFRAMETIME 33
#define STARTUPFRAMES 60
extern int frameNumber;
extern txtlog *gfxErrorLog;
void logGfxError(std::string precedingMessage);
#endif

#endif
