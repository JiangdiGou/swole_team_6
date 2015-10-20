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
  SpriteText(std::string initialMessage);

  void Update(float dt) override;

  std::string message;

  static void renderText(std::string message, Vector3 position, Vector3 scale);
  void static SpriteText::initText(const Shader& shader, Texture* font);
  static void drawAllText();

private:
  static GLuint shaderID;
  static Texture *pFont;

  static std::map<char, glm::vec2> offsets;
  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;

  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;

  static void loadCharacters();
};

#endif