#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "Graphics.h"
#include "Shader.h"


class DebugDraw
{
public:
	DebugDraw();
	friend void debugDrawLine(glm::vec3 startPoint, glm::vec3 endPoint,
		glm::vec3 color);
	friend void debugDrawSquare(glm::vec3 center, float width, float height,
		glm::vec3 color);
	friend void debugDrawSquare(glm::vec3 topLeft, glm::vec3 topRight,
		glm::vec3 bottomLeft, glm::vec3 bottomRight,
		glm::vec3 color);
	friend void debugDrawCircle(glm::vec3 center, float radius, glm::vec3 color,
		int segments);
	friend void debugDrawArrow(glm::vec3 startPoint, glm::vec3 endPoint,
		glm::vec3 color);

	friend void initDebugDraw(Shader shader);
	friend void debugDrawFrame(void);
private:
	static std::vector<GLfloat> debugVertices;
	static std::vector<GLfloat> debugColors;
	static GLuint vertexArray;
	static GLuint vertexBuffer;
	static GLint transformLocation;
	static GLint colorLocatgion;
	static Shader *pShader;
};

#endif DEBUGDRAW_H  