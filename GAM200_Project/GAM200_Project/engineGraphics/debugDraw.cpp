#include "debugDraw.h"

std::vector<GLfloat> debugVertices = {};
std::vector<GLfloat> debugColors = {};
GLuint vertexArray = -1;
GLuint vertexBuffer = -1;
GLint transformLocation = -1;
GLint colorLocation = -1;
Shader *pShader = NULL;

void initDebugDraw(Shader shader)
{
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//lyout,size,type,normalized,stride,offset
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		(GLvoid*)0);

	/*
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
	(GLvoid*)(3 * sizeof(GLfloat)));
	*/
	//Gets uniform locations from shader 
	transformLocation = glGetUniformLocation(shader.Program, "uniformTransform");
	colorLocation = glGetUniformLocation(shader.Program, "uniformColor");

	glLineWidth(1.0f);
	pShader = &shader;
	glBindVertexArray(0);
}

void debugDrawFrame(void)
{
	//Prepares to Draw
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, debugVertices.size() * sizeof(GLfloat), debugVertices.data(), GL_STATIC_DRAW);

	pShader->Use();
	//std::cout << pShader->Program << std::endl;

	if (pShader == NULL)
		std::cout << "Debug Draw: pShader is null";

	//Sends Idenity Matrix to Shader
	//transformLocation = glGetUniformLocation(pShader->Program, "uniformTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE,
		glm::value_ptr((glm::mat4())));

	//colorLocation = glGetUniformLocation(pShader->Program, "uniformColor");
	//std::cout << colorLocation << std::endl;
	glUniform4f(colorLocation, 0.0f, 1.0f, 0.0f, 1.0f);
	glDrawArrays(GL_LINES, 0, debugVertices.size() / 3.0f);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	debugVertices.clear();
}

void debugDrawLine(Vector3 startPoint, Vector3 endPoint, Vector3 color)
{
	debugVertices.push_back(startPoint.x);
	debugVertices.push_back(startPoint.y);
	debugVertices.push_back(startPoint.z);
	debugVertices.push_back(endPoint.x);
	debugVertices.push_back(endPoint.y);
	debugVertices.push_back(endPoint.z);
}

void debugDrawSquare(Vector3 center, float width, float height, Vector3 color)
{
	debugDrawLine(
    Vector3((center.x - 0.5*width), (center.y + 0.5*height), center.z),
    Vector3((center.x + 0.5*width), (center.y + 0.5*height), center.z),
    Vector3());
	debugDrawLine(
    Vector3((center.x + 0.5*width), (center.y + 0.5*height), center.z),
    Vector3((center.x + 0.5*width), (center.y - 0.5*height), center.z),
    Vector3());
	debugDrawLine(
    Vector3((center.x + 0.5*width), (center.y - 0.5*height), center.z),
    Vector3((center.x - 0.5*width), (center.y - 0.5*height), center.z),
    Vector3());
	debugDrawLine(
    Vector3((center.x - 0.5*width), (center.y - 0.5*height), center.z),
    Vector3((center.x - 0.5*width), (center.y + 0.5*height), center.z),
    Vector3());
}

void debugDrawSquare(Vector3 topLeft, Vector3 topRight,
  Vector3 bottomLeft, Vector3 bottomRight, Vector3 color)
{
  debugDrawLine(topLeft, topRight, Vector3());
  debugDrawLine(topRight, bottomRight, Vector3());
  debugDrawLine(bottomRight, bottomLeft, Vector3());
  debugDrawLine(bottomLeft, topLeft, Vector3());
}

void debugDrawCircle(Vector3 center, float radius, Vector3 color, int segments)
{
	float angle, angle2, x, x2, y, y2;
	for (int i = 1; i <= 2 * segments; ++i)
	{
		angle = 2 * 3.1415 * (float(i) / float(2 * segments));
		x = cos(angle);
		y = sin(angle);

		angle2 = 2 * 3.1415 * (float(i + 1) / float(2 * segments));
		x2 = cos(angle2);
		y2 = sin(angle2);

		debugDrawLine(
		Vector3((center.x + radius*x), (center.y + radius*y), center.z),
    Vector3((center.x + radius*x2), (center.y + radius*y2), center.z),
    Vector3());
	}
}

