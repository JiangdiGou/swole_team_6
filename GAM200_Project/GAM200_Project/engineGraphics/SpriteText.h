/*****************************************************************************/
/*!
\file    SpriteText.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of sprite text, which allows text to be displayed
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef SPRITETEXT_H
#define SPRITETEXT_H

#include <map>
#include <string>
#include "../physicsLib/Transform.h"
#include "../Composition.h"
#include "Shader.h"
#include "Texture.h"
#include "../Zilch/BindInternal.hpp"
#include "../Zilch/Zilch.hpp"

using namespace Zilch;

class SpriteText : public GameComponent
{
public:
  ZilchDeclareDerivedType(SpriteText, GameComponent);
  SpriteText();
  SpriteText(std::string initialMessage);

  void Update(float dt) override;
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

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
