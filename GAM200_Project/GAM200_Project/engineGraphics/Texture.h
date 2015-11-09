/*****************************************************************************/
/*!
\file    Texture.h
\author  Conor Lavelle
\par     Contact: c.lavelle@digipen.edu
\brief 
  See texture.cpp
\remarks 
  

All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
//~EndHeader~
#ifndef TEXTURE_H
#define TEXTURE_H

#include "Graphics.h"

//Image Loading 
#include "SOIL/SOIL.h"


class Texture
{
  friend class SpriteText;

public:
  //Default constructor, does nothing
  Texture();
  //Constructor for not animated textures
  Texture(const char* fileName);
  //Constructor for animated textures 
  Texture(const char* fileName, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);
  //Constructor for animated textures in a larger atlas
  Texture(const char* fileName, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration, int startOffsetX, int startOffsetY);
  //Destructor
  ~Texture();

  GLuint ID;

  int numFrames;
  int currentFrame;
  float frameDuration;

  void updateAnimation(void);

  //12 because our basic square has 6 verticies as well as 
  //2 texture coordinates, x and y, for each vertex. 
  GLfloat textureCoordinates[12];

private:
  int offsetXBytes;
  int offsetYBytes;
  int numRows;
  int numColumns;
  float width;
  float height;
  float frameStartTime;
  GLfloat getLeftX();
  GLfloat getRightX();
  GLfloat getTopY();
  GLfloat getBottomY();

};

#endif
