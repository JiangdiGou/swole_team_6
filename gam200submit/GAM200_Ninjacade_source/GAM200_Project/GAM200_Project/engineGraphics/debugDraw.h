/*****************************************************************************/
/*!
\file       debugDraw.h
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     Interface of our game's debug drawing system
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "Graphics.h"
#include "Shader.h"
#include "../physicsLib/math_utility.h"


class DebugDraw
{
public:
	DebugDraw();
  friend void debugDrawLine(Vector3 startPoint, Vector3 endPoint,
    Vector3 color);
  friend void debugDrawSquare(Vector3 center, float width, float height,
    Vector3 color);
  friend void debugDrawSquare(Vector3 topLeft, Vector3 topRight,
    Vector3 bottomLeft, Vector3 bottomRight,Vector3 color);
  friend void debugDrawCircle(Vector3 center, float radius, Vector3 color,
		int segments);

	friend void initDebugDraw(const Shader& shader);
	friend void debugDrawFrame(void);
private:
	static std::vector<GLfloat> debugVertices;

	static GLuint vertexArray;
	static GLuint vertexBuffer;
  static GLuint shaderID;
};

#endif DEBUGDRAW_H  
