/*****************************************************************************/
/*!
\file       instancedSprite.h
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     UNUSED SHOULD DELETE
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#ifndef  ISPRITE_H
#define ISPRITE_H

#include "Shader.h"
#include <vector>
#include "Texture.h"

class ISprite
{
  //This may or may not be necessary, not sure yet 

public:
  //Default constructor,
  ISprite();
  //Deconstructor 
  ~ISprite();

  //Transformations
  glm::vec3 translation;
  GLfloat rotation;
  glm::vec3 scale;


  //Color and Texture
  glm::vec4 color;
  Texture texture;

  void static drawSprites(Texture testTexture);
  static std::vector<ISprite*> Isprites;

  static void Load(Shader spriteShader);
  static void Unload(void); 

private:
  //Vertex information 
  static GLuint vertexArray;
  static GLuint positionBuffer;
  static GLuint texCoordsBuffer;
  static GLuint colorBuffer; 
  static GLuint matrixBuffer;

  static std::vector<GLfloat> transformMatrices;
  static std::vector<GLfloat> textureCoordinatesAll;
  static std::vector<GLfloat> colorValues;

  static Shader* shader; 

  //A sprite's personal draw function, called by drawsprites 
  void prepareDraw(void);

  //Calculates a sprite's transformation matrix using the 
  glm::mat4 calculateTransorm(void);

};

#endif 
