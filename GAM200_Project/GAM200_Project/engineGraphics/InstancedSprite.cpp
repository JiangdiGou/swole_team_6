/*****************************************************************************/
/*!
\file       InstancedSprite.cpp
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     UNUSED SHOULD DELETE
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#include "InstancedSprite.h"

//Initalize Static Member of Class
std::vector<ISprite*> ISprite::Isprites = {};

GLuint ISprite::vertexArray = 0;
GLuint ISprite::positionBuffer = 0;
GLuint ISprite::texCoordsBuffer = 0;
GLuint ISprite::colorBuffer = 0;
GLuint ISprite::matrixBuffer = 0;

std::vector<GLfloat> ISprite::transformMatrices = {};
std::vector<GLfloat> ISprite::textureCoordinatesAll = {};
std::vector<GLfloat> ISprite::colorValues = {};

Shader* ISprite::shader = NULL;

void ISprite::Load(Shader spriteShader)
{
	spriteShader.Use();

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

  //The vertex data will never change, so send that data now. 
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  //For vertex Position
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);

  //For texture coordinates
  glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(GLfloat), (GLvoid*)0);

  //For Color
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

  //For Transformation Matrix
  glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
  for (int i = 0; i < 4; ++i)
  {
	  glEnableVertexAttribArray(3 + i);
	  glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, 
		  4 * 4 * sizeof(GLfloat), (GLvoid*)(4 * i * sizeof(GLfloat)));
  }

  glBindVertexArray(vertexArray);
  glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
  glBindVertexArray(0);

  glVertexAttribDivisor(positionBuffer, 0);
  glVertexAttribDivisor(texCoordsBuffer, 1);
  glVertexAttribDivisor(colorBuffer, 1);
  glVertexAttribDivisor(matrixBuffer, 1);
  glVertexAttribDivisor(matrixBuffer + 1, 1);
  glVertexAttribDivisor(matrixBuffer + 2, 1);
  glVertexAttribDivisor(matrixBuffer + 3, 1);

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
  glm::mat4 transform = calculateTransorm();

  for (int i = 0; i < 4; ++i)
  {
	  for (int j = 0; j < 4; ++j)
	    ISprite::transformMatrices.push_back(transform[i][j]);
  }

  texture.updateAnimation();
  for (int i = 0; i < 12; ++i)
    ISprite::textureCoordinatesAll.push_back(texture.textureCoordinates[i]);
 
  ISprite::colorValues.push_back(color.x);
  ISprite::colorValues.push_back(color.y);
  ISprite::colorValues.push_back(color.z);
  ISprite::colorValues.push_back(color.w);
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

  for (std::vector<ISprite*>::iterator it = Isprites.begin(); it != Isprites.end(); ++it)
    (*it)->prepareDraw();

  glBindVertexArray(vertexArray);
  glBindTexture(GL_TEXTURE_2D, testTexture.ID);

  //Bind texture here if you want textures to work. if not, a single texture atlas will be bound
  glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
  glBufferData(GL_ARRAY_BUFFER, textureCoordinatesAll.size() * sizeof(GLfloat),
	  textureCoordinatesAll.data(), GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
  glBufferData(GL_ARRAY_BUFFER, colorValues.size() * sizeof(GLfloat),
	  colorValues.data(), GL_STREAM_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, matrixBuffer);
  glBufferData(GL_ARRAY_BUFFER, transformMatrices.size() * sizeof(GLfloat),
	  transformMatrices.data(), GL_STREAM_DRAW);

  glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, Isprites.size());

  textureCoordinatesAll.clear();
  colorValues.clear();
  transformMatrices.clear();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
}
