//ALSO STUFF
#ifndef ATLASTEXTURE_H
#define ATLASTEXTURE_H

#include "Graphics.h"

class AtlasTexture
{
public:
  AtlasTexture(int atlasWidth, int atlasHeight, int numberOfFrames,
    int frameTime, int xOffset, int yOffset, int textureWidth, int textureHeight);

  void updateAnimation(void);
  GLfloat textureCoordinates[12];
private:
  int currentFrame;
  int numFrames;

  int numRows;
  int numColumns;

  int offsetX;
  int offsetY;

  int atlasWidth;
  int atlasHeight;
  //neeeded?
  //int atlasID;

  //ms
  int frameStartTime;
  int frameDuration;



  GLfloat getLeftX();
  GLfloat getRightX();
  GLfloat getTopY();
  GLfloat getBottomY();
};


#endif