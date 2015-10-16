#ifndef  SPRITE_H
#define SPRITE_H

#include "Shader.h"
#include <vector>
#include "AtlasTexture.h"
#include "textureAtlas.h"
#include "../physicsLib/Transform.h"
#include "../Composition.h"

class Sprite : public GameComponent
{
public:
  //Default constructor, just sets color member
  Sprite();
  ~Sprite();

	glm::vec4 color;
	AtlasTexture texture;

  void Update() override;

  static void initSprites(const Shader& shader, const TextureAtlas& atlas);
  void static drawAllSprites();

private:
  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;
  static GLuint shaderID;
  static GLuint atlasID;

  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;

  //Helper Function, pushes xyz to vertices
  void pushVertices(const glm::vec4 &verts);
};

#endif 
