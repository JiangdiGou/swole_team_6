#ifndef SPRITETEXT_H
#define SPRITETEXT_H

#include <map>
#include <string>
#include "../physicsLib/Transform.h"
#include "../Composition.h"
#include "Shader.h"
#include "Texture.h"

class SpriteText : public GameComponent
{
public:
  void static SpriteText::initText(Shader* shader, Texture* font);
  static void drawAllText();
  static void renderText(std::string message, Vector3 position, Vector3 scale);
  SpriteText(std::string initialMessage);

  void Update() override;

  std::string message;

private:
  static Shader *pShader;
  static Texture *pFont;

  static std::map<char, glm::vec2> offsets;
  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;

  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;
  static GLint transformLocation;

  static void loadCharacters();

};

#endif