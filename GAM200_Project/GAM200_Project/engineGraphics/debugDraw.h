#ifndef DEBUGDRAW_H
#define DEBUGDRAW_H

#include "Graphics.h"
#include "Shader.h"

void debugDrawLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color, Shader debugShader);

void debugDrawSquare(glm::vec3 center, float width, float height,
                     glm::vec3 color);
void debugDrawSquare(glm::vec3 topLeft, glm::vec3 topRight, 
                     glm::vec3 bottomLeft, glm::vec3 bottomRight, 
                     glm::vec3 color);

void debugDrawCircle(glm::vec3 center, float radius, glm::vec3 color);

void debugDrawArrpw(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color);

#endif DEBUGDRAW_H  