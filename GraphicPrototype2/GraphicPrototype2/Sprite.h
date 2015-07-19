#ifndef  SPRITE_H
#define SPRITE_H

#include "Graphics.h"
#include "Shader.h"
#include <vector>

class Sprite
{
public:
	//Default constructor does nothing
	Sprite();
	//Constructor makes a square
	Sprite(Shader intendedShader);
	//Deconstructor 
	~Sprite();

	//Core Drawing
	void Draw(void);
	GLuint vertexArray;

	//Transformations
	glm::vec3 translation;
	GLfloat rotation;
	glm::vec3 scale;
	glm::mat4 calculateTransorm(void);

	//Color and Texture
	glm::vec4 color;
	GLuint texture;

private:
	GLuint vertexBuffer;
	Shader shader;

};

extern std::vector<Sprite*> sprites;
void drawSprites(void);

#endif 
