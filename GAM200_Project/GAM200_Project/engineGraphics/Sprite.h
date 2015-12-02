/*****************************************************************************/
/*!
\file    Sprite.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  Interface of Sprite, which is the core graphical component of our game
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef  SPRITE_H
#define SPRITE_H

#include "Shader.h"
#include <vector>
#include "AtlasTexture.h"
#include "textureAtlas.h"
#include "../physicsLib/Transform.h"
#include "../Composition.h"
#include "../Message.h"
#include "../WindowsSystem.h"
#include "../Zilch/BindInternal.hpp"
#include "../Zilch/Zilch.hpp"

using namespace Zilch;

class Sprite : public GameComponent
{
public:
  ZilchDeclareDerivedType(Sprite, GameComponent);
  //Default constructor, just sets color member
  Sprite();
  ~Sprite();

	glm::vec4 color;
	AtlasTexture texture;

  void Initialize();
  void Update(float dt) override;
  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

  void setTexture(std::string newTexture)
  {
    texture = atlas->textures[newTexture];
  }

  static void initSprites(const Shader& shader, TextureAtlas* spriteAtlas);
  void static drawAllSprites();

  bool flipSprite = false;
  bool visible = true; 
  float GetColorX();
  float GetColorY();
  float GetColorZ();
  float GetColorW();
  void SetColorX(float val);
  void SetColorY(float val);
  void SetColorZ(float val);
  void SetColorW(float val);
private:
  static TextureAtlas* atlas;

  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;
  static GLuint colorBuffer;
  static GLuint shaderID;
  static GLuint atlasID;

  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;
  static std::vector<GLfloat> colors;

  void SendMessages(Message * message) override;

  //Helper Function, pushes xyz to vertices
  void pushVertices(const glm::vec4 &verts);

  bool facingRight = true;
};

#endif 
