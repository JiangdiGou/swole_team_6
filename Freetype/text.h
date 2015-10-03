#ifndef TEXT_H
#define TEXT_H

#pragma comment(lib, "graphicsLibsWin/freetype26_D.lib")

#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include "Shader.h"
#include <map>
#include <string>
#include "../physicsLib/Transform.h"
#include "../Composition.h"

struct Character
{
  GLuint textureID;  //Handle
  //This is mathmatical information about the character that i hopefully
  //will be able to use later to make the rendered text look less bad
  glm::ivec2 size;
  glm::ivec2 bearing; //Offset from baseline to top of glyph
  GLuint advance;     //Offset to next glyph
};

class Text : public GameComponent
{
public:
  Text(std::string initialMessage, Shader textShader);
  void Update() override;

  static void initText(Shader shader);

  std::string message;
  //glm::vec3 translation;
  //glm::vec3 scale;


private:
  Shader shader;
  glm::mat4 calculateTransform(void);
  static std::map<GLchar, Character> characters;
  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;
  //Void b/c acts on the map characters 
  static void generateTexturesFromFont(FT_Face face);
};


#endif