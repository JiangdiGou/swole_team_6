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
  static void initSprites(Shader shader);

  //Default constructor, does nothing
	Sprite();
  //Constructor from shader 
  Sprite(Shader intendedShader);
	//Deconstructor 
	~Sprite();

	//Color and Texture
	glm::vec4 color;
	Texture texture;

  void Update() override;

  void static Sprite::drawAllSprites();

  //void static drawSprites(void);  
  static std::vector<Sprite*> sprites;

private:
  static Shader* pShader;

  static std::vector<GLfloat> vertices;
  static std::vector<GLfloat> texCoords;

  static GLuint vertexArray;
	static GLuint vertexBuffer;
  static GLuint textureBuffer;

  Shader shader;

  //A sprite's personal draw function, called by drawsprites 
  void draw(void);

  void pushVertices(const glm::vec4 &verts);

};

#endif 
