#ifndef TEXTURE_H
#define TEXTURE_H

#include "Graphics.h"

class Texture
{

public:
  //Default constructor, does nothing
  Texture();
  //Constructor for not animated textures
  Texture(const char* fileName);
  //Constructor for animated textures 
  Texture(const char* fileName, int numberOfFrames, int frameWidth, int frameHeight, float frameDuration);
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
  int numRows;
  int numColumns;
  float frameStartTime;
  GLfloat getLeftX();
  GLfloat getRightX();
  GLfloat getTopY();
  GLfloat getBottomY();



};

#endif