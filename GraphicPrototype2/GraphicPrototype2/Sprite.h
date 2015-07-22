#ifndef  SPRITE_H
#define SPRITE_H

#include "Shader.h"
#include <vector>

class Sprite
{
public:
  //Default constructor, does nothing
	Sprite();
  //
  Sprite(Shader intendedShader);
	//Deconstructor 
	~Sprite();

	//Transformations
	glm::vec3 translation;
	GLfloat rotation;
	glm::vec3 scale;


	//Color and Texture
	glm::vec4 color;
	GLuint texture;

  void static drawSprites(void);
  static std::vector<Sprite*> sprites;

private:
  //Vertex information 
	GLuint vertexBuffer;
  GLuint vertexArray;

  Shader shader;

  //A sprite's personal draw function, called by drawsprites 
  void draw(void);

  //Calculates a sprite's transformation matrix using the 
  glm::mat4 calculateTransorm(void);

};

#endif 
