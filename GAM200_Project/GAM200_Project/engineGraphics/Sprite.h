#ifndef  SPRITE_H
#define SPRITE_H

#include "Shader.h"
#include <vector>
#include "Texture.h"
#include "../physicsLib/Transform.h"
#include "../Composition.h"

class Sprite : public GameComponent
{
  //This may or may not be necessary, not sure yet 

public:
  //Default constructor, does nothing
	Sprite();
  //Constructor from shader 
  Sprite(Shader intendedShader);
	//Deconstructor 
	~Sprite();

	//Transformations
  /*
	glm::vec3 translation;
	GLfloat rotation;
	glm::vec3 scale;
  */

	//Color and Texture
	glm::vec4 color;
	Texture texture;

  void Update() override;

  void static drawSprites(void);  
  static std::vector<Sprite*> sprites;

private:
  //Vertex information 
	GLuint vertexBuffer;
  GLuint textureBuffer;
  GLuint vertexArray;

  Shader shader;

  //A sprite's personal draw function, called by drawsprites 
  void draw(void);

  //Calculates a sprite's transformation matrix using the 
  glm::mat4 calculateTransorm(void);

};

#endif 
