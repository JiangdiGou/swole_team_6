#ifndef  SPRITESWITCHER_H
#define SPRITESWITCHER_H

#include "Shader.h"
#include <vector>
#include "AtlasTexture.h"
#include "textureAtlas.h"
#include "../physicsLib/Transform.h"
#include "../Composition.h"
#include "../Message.h"
#include "../WindowsSystem.h"

class SpriteSwitcher : public GameComponent
{
public:
  //Default constructor, just sets color member
  SpriteSwitcher();

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
