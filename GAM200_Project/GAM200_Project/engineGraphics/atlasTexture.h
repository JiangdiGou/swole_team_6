#ifndef ATLASTEXTURE_H
#define ATLASTEXTURE_H

#include "Graphics.h"

class AtlasTexture
{
public:
  AtlasTexture(int aWidth, int aHeight, int numberOfFrames,
    int frameTime, int xOffset, int yOffset, int textureWidth, int textureHeight);
  AtlasTexture();

  void updateAnimation(void);
  GLfloat textureCoordinates[12];
private:
  //Literally every private member here is used for animation 
  int currentFrame;
  int numFrames;
  int numRows;
  int numColumns;
  int offsetX;
  int offsetY;
  int atlasWidth;
  int atlasHeight;
  //ms
  int frameStartTime;
  int frameDuration;

  //Helper functions used by update animation
  GLfloat getLeftX();
  GLfloat getRightX();
  GLfloat getTopY();
  GLfloat getBottomY();
};


#endif