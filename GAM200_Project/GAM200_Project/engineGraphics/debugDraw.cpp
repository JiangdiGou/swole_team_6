#include "debugDraw.h"

void debugDrawLine(glm::vec3 startPoint, glm::vec3 endPoint, glm::vec3 color, Shader debugShader)
{
  GLint transformLocation, colorLocation;
  GLfloat lineCoordinates[] = { startPoint.x, startPoint.y,
                               endPoint.x, endPoint.y};
  GLuint vertexArray, vertexBuffer;

  glLineWidth(1.0f);

  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);

  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  debugShader.Use();

  //Copies the Vertex data into the buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(lineCoordinates), lineCoordinates, GL_STATIC_DRAW);

  //Activates Vertex Position Information
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    2,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    2 * sizeof(GLfloat), // stride
    (GLvoid*)0            // array buffer offset
    );


  //Sends the sprite's color information in the the shader 
  colorLocation = glGetUniformLocation(debugShader.Program, "uniformColor");
  glUniform4f(colorLocation, 1.0f, color.x, color.y, color.z);

  // Draw the line !
  glDrawArrays(GL_LINES, 0, 2); // 2 indices for the 2 end points of 1 line

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  std::cout << glGetError() << std::endl;
}
