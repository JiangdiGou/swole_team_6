#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "Shader.h"
#include <map>
#include <string>
#include "../Composition.h"

struct Character
{
  GLuint textureID;  //Handle
  glm::ivec2 size;
  glm::ivec2 bearing; //Offset from baseline to top of glyph
  GLuint advance;     //Offset to next glyph
};

class Text : public GameComponent
{
public:
  Text();
  ~Text();
  Text(std::string initialMessage);

  void RenderText(GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
  void Update() override;

  static void initText(Shader shader);

  std::string message;
  glm::vec3 color;
  glm::vec3 translation;
  float scale;

private:
  static Shader* shader;
  static std::map<GLchar, Character> characters;
  static GLuint vertexArray;
  static GLuint vertexBuffer;
};


#endif