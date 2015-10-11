#ifndef  SPRITE_H
#define SPRITE_H

#include "Shader.h"
#include <vector>
#include "Texture.h"
#include "../physicsLib/Transform.h"
#include "../Composition.h"

class Sprite : public GameComponent
{
public:
  //Default constructor, just sets color member
  Sprite();
  ~Sprite();

	glm::vec4 color;
	Texture texture;

  void Update() override;

  static void initSprites(const Shader& shader);
  void static drawAllSprites();

private:
  static GLuint vertexArray;
  static GLuint vertexBuffer;
  static GLuint textureBuffer;
  static GLuint shaderID;

  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;

  //Helper Function, pushes xyz to vertices
  void pushVertices(const glm::vec4 &verts);
};

#endif 
