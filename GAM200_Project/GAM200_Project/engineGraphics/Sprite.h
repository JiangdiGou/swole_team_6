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

class Sprite : public GameComponent
{
public:
  //Default constructor, just sets color member
  Sprite();
  ~Sprite();

	glm::vec4 color;
  std::string textureName;
	AtlasTexture texture;

  void Update(float dt) override;

  void SerializeRead(Serializer& str) override;
  void SerializeWrite(Serializer& str) override;

  static void initSprites(const Shader& shader, const TextureAtlas& atlas);
  void static drawAllSprites();

  bool flipSprite = false;

private:
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
