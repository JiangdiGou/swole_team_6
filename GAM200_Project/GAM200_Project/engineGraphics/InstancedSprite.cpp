#include "InstancedSprite.h"

//Initalize Static Member of Class
std::vector<ISprite*> ISprite::Isprites = {};

GLuint ISprite::vertexArray = 0;
GLuint ISprite::positionBuffer = 0;
GLuint ISprite::texCoordsBuffer = 0;
GLuint ISprite::colorBuffer = 0;
GLuint ISprite::matrixBuffer = 0;

std::vector<glm::mat4> ISprite::transformMatrices = {};
std::vector<GLfloat> ISprite::textureCoordinatesAll = {};
std::vector<GLfloat> ISprite::colorValues = {};

Shader* ISprite::shader = NULL;

void ISprite::Load(Shader spriteShader)
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

  glGenVertexArrays(1, &vertexArray);
  glGenBuffers(1, &positionBuffer);
  glGenBuffers(1, &texCoordsBuffer);
  glGenBuffers(1, &colorBuffer);
  glGenBuffers(1, &matrixBuffer);

  glBindVertexArray(vertexArray);

  //For vertex Position
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

  //The vertex data will never change, so send that data now. 
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //For texture coordinates
  glEnableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

  //For Color
  glEnableVertexAttribArray(2);
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

  //For Transformation Matrix
  glEnableVertexAttribArray(3);
  glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
  glVertexAttribPointer(3, 1, GL_MATRIX4_ARB, GL_FALSE, 0, (GLvoid*)0);

  //Unbind
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  //Sets up support for instancing
  glVertexAttribDivisor(0, 0); 
  glVertexAttribDivisor(1, 1); 
  glVertexAttribDivisor(2, 1);
  glVertexAttribDivisor(3, 1);

  ISprite::shader = &spriteShader;
}


void ISprite::Unload()

{
  glDeleteBuffers(1, &positionBuffer);
  glDeleteBuffers(1, &texCoordsBuffer);
  glDeleteBuffers(1, &colorBuffer); 
}

//**********************
//Function    : Sprite
//Input       : intendedShader - the shader you intend to use with the sprite
//Output      : Sprite - The constructed Sprite 
//Description : Constructor for the sprite class 
//**********************
ISprite::ISprite()
{
  scale = glm::vec3(1.0f, 1.0f, 1.0f);
  translation = glm::vec3(0.0f, 0.0f, 0.0f);
  rotation = 0;
  color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

  ISprite::Isprites.push_back(this);
}


//**********************
//Function    : Sprite
//Input       : none
//Output      : none
//Description : deConstructor for sprite, frees resources
//**********************
ISprite::~ISprite()
{
  //Dunno if i need to remove this from the vector? 
}

//**********************
//Function    : Sprite.calculateTransform
//Input       : none
//Output      : mat4 - the calculated transformation matrix 
//Description : calculates the transformation matrix of a sprite. 
//**********************
glm::mat4 ISprite::calculateTransorm(void)
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
void ISprite::prepareDraw(void)
{
  //Adds their personal data to vectors shared by class 
  transformMatrices.push_back(calculateTransorm());

  for (int i = 0; i < 6; i += 2)
  {
    texture.updateAnimation();
    ISprite::textureCoordinatesAll.push_back(texture.textureCoordinates[i]);
    ISprite::textureCoordinatesAll.push_back(texture.textureCoordinates[i + i]);
  }

  ISprite::colorValues.push_back(color.x);
  ISprite::colorValues.push_back(color.y);
  ISprite::colorValues.push_back(color.z);
}

//**********************
//Function    : Sprite.drawSprites
//Input       : none
//Output      : none
//Description : draws all sprites
//**********************
void ISprite::drawSprites(Texture testTexture)
{
  shader->Use();
  glBindTexture(GL_TEXTURE_2D, testTexture.ID);

  for (std::vector<ISprite*>::iterator it = Isprites.begin(); it != Isprites.end(); ++it)
    (*it)->prepareDraw();

  glBindVertexArray(vertexArray);
  //Bind texture here if you want textures to work. if not, a single texture atlas will be bound
  glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
  glBufferData(GL_ARRAY_BUFFER, textureCoordinatesAll.size() * sizeof(GLfloat),
                NULL, GL_STREAM_DRAW);  
  glBufferSubData(GL_ARRAY_BUFFER, 0, textureCoordinatesAll.size() * sizeof(GLfloat), 
                textureCoordinatesAll.data());

  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, colorValues.size() * sizeof(GLfloat),
              NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, colorValues.size() * sizeof(GLfloat),
               colorValues.data());

  glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
  glBufferData(GL_ARRAY_BUFFER, transformMatrices.size() * sizeof(glm::mat4),
              NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, transformMatrices.size() * sizeof(glm::mat4),
              transformMatrices.data());

  glDrawArraysInstanced(GL_TRIANGLES, 0, 6, Isprites.size());

  textureCoordinatesAll.clear();
  colorValues.clear();
  transformMatrices.clear();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}