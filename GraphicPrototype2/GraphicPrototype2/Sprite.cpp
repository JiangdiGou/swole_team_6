#include "Sprite.h"

//Initalize Static Member of Class
std::vector<Sprite*> Sprite::sprites = {};

//**********************
//Function    : Sprite
//Input       : none
//Output      : Sprite - The Constrcuted Sprite 
//Description : Default Constructor for Sprite, does nothing
//**********************
Sprite::Sprite()
{
  std::cout << "ERROR: Sprite was Implicitly Constructed." << std::endl;
	std::cout << "Sprite requires shader to construct properly." << std::endl;
}

//**********************
//Function    : Sprite
//Input       : intendedShader - the shader you intend to use with the sprite
//Output      : Sprite - The constructed Sprite 
//Description : Constructor for the sprite class 
//**********************
Sprite::Sprite(Shader intendedShader)
{
  GLfloat vertices[] = {
    //X    Y     Z     
    0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f
  };

  GLfloat texCoords[] = {
    //X   Y
    0.0f, 1.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
  };

	//Generates their IDs and saves them in vars
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &textureBuffer);

	//Binds the VAO and VBO so future GL fx calls will affet them
	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	//Copies the Vertex data into the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Tells openGL how to interpret this array of random numbers
	//glVertexAttribPointer
	//Param 1: Location. Which attribute in the vertex shader we're setting up
	//Param 2: Size. How many values the vertex attribute has 
	//Param 3: Type. What type the vertex attributes are
	//Param 4: Normalization. Whether or not the values should be normalized 
	//Param 5: Stride. Space in bytes between attribute sets 
	//Param 6: Offset. After how many bytes the info begins (cast as glvoid*)

	//Sets up Vertex position information
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
		(GLvoid*)0);
	//Activates Vertex Position Information
	glEnableVertexAttribArray(0);

  //Binds the texture buffer and sends it data 
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	//Sets up Texture coordinate information 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
		(GLvoid*)0);
	//Activates texture coordinate information 
	glEnableVertexAttribArray(1);

	//We're done with the buffers now, so unbinds them 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Initalizes remaining members
	shader = intendedShader;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = 0;
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  sprites.push_back(this);
}

//**********************
//Function    : Sprite
//Input       : none
//Output      : none
//Description : deConstructor for sprite, frees resources
//**********************
Sprite::~Sprite()
{
  //De allocates resources 
  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &textureBuffer);
}

//**********************
//Function    : Sprite.calculateTransform
//Input       : none
//Output      : mat4 - the calculated transformation matrix 
//Description : calculates the transformation matrix of a sprite. 
//**********************
glm::mat4 Sprite::calculateTransorm(void)
{
	glm::mat4 transform;
	transform = glm::translate(transform, translation);
	//Since we're in 2d, rotation occurs about the Z axis
	//Can be changed later if you want different types of rotation
	transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, scale);

	return transform;
}

//**********************
//Function    : Sprite.draw
//Input       : none
//Output      : none
//Description : animated sprite if necessary, draws sprite on screen 
//**********************
void Sprite::draw(void)
{
	GLint transformLocation, colorLocation;

	glBindVertexArray(vertexArray);
	glBindTexture(GL_TEXTURE_2D, texture.ID);

  //If the Sprite's texture should animate 
  if (texture.numFrames > 1)
  {
    texture.updateAnimation();
    glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 12, texture.textureCoordinates);
  }
  
	//Sends the sprite's transformation matrix into the shader
	transformLocation = glGetUniformLocation(shader.Program, "uniformTransform");
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE,
			              glm::value_ptr(calculateTransorm()));

	//Sends the sprite's color information in the the shader 
	colorLocation = glGetUniformLocation(shader.Program, "uniformColor");
	glUniform4f(colorLocation, color.w, color.x, color.y, color.z);

	glDrawArrays(GL_TRIANGLES, 0, 6);

  //Unbinds the texture, buffer, and vertex array 
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

//**********************
//Function    : Sprite.drawSprites
//Input       : none
//Output      : none
//Description : draws all sprites
//**********************
void Sprite::drawSprites(void)
{
  for (std::vector<Sprite*>::iterator it = sprites.begin(); it != sprites.end(); ++it)
    (*it)->draw();
}
