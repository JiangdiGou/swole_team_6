#ifndef GRAPHICS_H
#define GRAPHICS_H

//Core Graphics Functionality 
#define GLEW_STATIC
#include <glew/glew.h>
#include <glew/wglew.h>

//Window Creation
#include <Windows.h>

//Image Loading 
#include <SOIL/SOIL.h>

//Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Printing out stuff
#include<iostream>

#define WINDOWWIDTH 960
#define WINDOWHEIGHT 540

GLuint  loadTexture(const char* filePath);
void setupPixelFormatDescriptor(HDC handleDeviceContext);
HWND createWindow(HINSTANCE instance);

//This function prototype is in here so createwindow can see it 
LRESULT CALLBACK WinProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


#endif
