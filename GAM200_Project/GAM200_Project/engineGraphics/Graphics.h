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

//Window Creation
#include <Windows.h>

//Image Loading 
#include "SOIL/SOIL.h"

//Math
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//Printing out stuff
#include<iostream>
#include "../logger/logger.h"
#include <vector>
#include <string>

#define WINDOWWIDTH 960
#define WINDOWHEIGHT 540

void setupPixelFormatDescriptor(HDC handleDeviceContext);
HWND createWindow(HINSTANCE instance);

//This function prototype is in here so createwindow can see it 
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

#define GFXLOG

#ifdef GFXLOG
#define WARNINGFRAMETIME 33
#define STARTUPFRAMES 5
extern int frameNumber;
extern txtlog *gfxErrorLog;
void logGfxError(std::string precedingMessage);
#endif

#endif
