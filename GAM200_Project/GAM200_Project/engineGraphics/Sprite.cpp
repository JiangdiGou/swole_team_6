#include "Sprite.h"

GLuint Sprite::shaderID = 0;
std::vector<GLfloat> Sprite::vertices = {};
std::vector<GLfloat> Sprite::texCoords = {};
GLuint Sprite::vertexArray = 0;
GLuint Sprite::vertexBuffer = 0;
GLuint Sprite::textureBuffer = 0;

//**********************
//Function    : Sprite
//Input       : none
//Output      : Sprite - The Constrcuted Sprite 
//Description : Default Constructor for Sprite, does nothing
//**********************/
/*
Sprite::Sprite()
{
  std::cout << "ERROR: Sprite was Implicitly Constructed." << std::endl;
	std::cout << "Sprite requires shader to construct properly." << std::endl;
}
*/

//**********************
//Function    : Sprite
//Input       : none
//Output      : Sprite - The constructed Sprite 
//Description : Constructor for the sprite class 
//**********************
Sprite::Sprite()
{
  /*
  //OLD, NON BATCH DRAWING SYSTEM
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
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

	//Tells openGL how to interpret this array of random numbers
	//glVertexAttribPointer
	//Param 1: Location. Which attribute in the vertex shader we're setting up
	//Param 2: Size. How many values the vertex attribute has 
	//Param 3: Type. What type the vertex attributes are
	//Param 4: Normalization. Whether or not the values should be normalized 
	//Param 5: Stride. Space in bytes between attribute sets 
	//Param 6: Offset. After how many bytes the info begins (cast as glvoid*)

	//Sets up Vertex position information
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//Activates Vertex Position Information
	glEnableVertexAttribArray(0);

  //Binds the texture buffer and sends it data 
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STREAM_DRAW);

	//Sets up Texture coordinate information 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//Activates texture coordinate information 
	glEnableVertexAttribArray(1);
  
	//We're done with the buffers now, so unbinds them 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
  */

	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

//**********************
//Function    : Sprite
//Input       : none
//Output      : none
//Description : deConstructor for sprite, frees resources
//**********************
Sprite::~Sprite()
{
}


//**********************
//Function    : Sprite.draw
//Input       : none
//Output      : none
//Description : animated sprite if necessary, draws sprite on screen 
//**********************
void Sprite::Update(void)
{
  /*
  //OLD NON BATCH DRAWING SYSTEM
  GLint transformLocation, colorLocation;
  Transform *transformComponent = GetOwner()->has(Transform);

	glBindVertexArray(vertexArray);
	glBindTexture(GL_TEXTURE_2D, texture.ID);

  shader.Use();

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
			              glm::value_ptr(transformComponent->calculateTransformMatrix()));
                    

	//Sends the sprite's color information in the the shader 
  
	colorLocation = glGetUniformLocation(shader.Program, "uniformColor");
	glUniform4f(colorLocation, color.w, color.x, color.y, color.z);


	glDrawArrays(GL_TRIANGLES, 0, 6);

  //Unbinds the texture, buffer, and vertex array 
  glBindTexture(GL_TEXTURE_2D, 0);
  //glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
  */
  
  
  glm::vec4 transformedPosition, initialPosition;
  glm::vec3 scale;

  glBindVertexArray(vertexArray);
  glUseProgram(shaderID);

  //Initialize vars I'm gonna need
  Transform *transform = GetOwner()->has(Transform);
  glm::mat4 transformMatrix = transform->calculateTransformMatrix();
  initialPosition = glm::vec4(
    transform->GetPosition().x,
    transform->GetPosition().y,
    transform->GetPosition().z,
    0);

  scale = glm::vec3(
    transform->GetScale().x,
    transform->GetScale().y,
    transform->GetScale().z);

  //Vertex 1
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x + 0.5 * scale.x,
    initialPosition.y - 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  //Vertex 2
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x - 0.5 * scale.x,
    initialPosition.y + 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  //Vertex 3
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x - 0.5 * scale.x,
    initialPosition.y - 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  //Vertex 4
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x + 0.5 * scale.x,
    initialPosition.y - 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  //Vertex 5
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x + 0.5 * scale.x,
    initialPosition.y + 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  //Vertex 6
  transformedPosition = glm::vec4(transformMatrix * glm::vec4(
    initialPosition.x - 0.5 * scale.x,
    initialPosition.y + 0.5 * scale.y,
    initialPosition.z, 0));
  pushVertices(transformedPosition);

  texture.updateAnimation();
  for (int i = 0; i < 12; ++i)
    texCoords.push_back(texture.textureCoordinates[i]);

  //Unbind Stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  
}

void Sprite::initSprites(const Shader& shader)
{
  //Generates Static Members
  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &vertexBuffer);
  glGenBuffers(1, &textureBuffer);

  //Binds VA and vertex buffer
  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

  //Set up vertex buffer information
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  //Set up texture buffer information
  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

  shaderID = shader.Program;

  //Unbind stuff
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Sprite::pushVertices(const glm::vec4 &verts)
{
  //W is not used. It's only a vec4 b/c of matrix mult
  vertices.push_back(verts.x);
  vertices.push_back(verts.y);
  vertices.push_back(verts.z);
}

void Sprite::drawAllSprites()
{
  glUseProgram(shaderID);

  //The binding of the atlas texture needs to go here 
  //glBindTexture(GL_TEXTURE_2D, texture.ID);

  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
  glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(GLfloat), texCoords.data(), GL_STREAM_DRAW);

  glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3.0f);
  glBindVertexArray(0);

  vertices.clear();
  texCoords.clear();
}