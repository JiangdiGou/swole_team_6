/*****************************************************************************/
/*!
\file       atlasTexture.h
\author  Conor Lavelle
\par        Contact: c.lavelle@digipen.edu
\brief 
     Interface of atlasTexture, which stores information about textures inside atlas
\remarks 
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
/*****************************************************************************/
#ifndef ATLASTEXTURE_H
#define ATLASTEXTURE_H

#include "Graphics.h"

class AtlasTexture
{
public:
  friend class Sprite;
  friend class TextureAtlas;

  AtlasTexture(int aWidth, int aHeight, int numberOfFrames,
    int frameTime, int xOffset, int yOffset, int textureWidth, int textureHeight);
  AtlasTexture();

  bool operator==(const AtlasTexture& rhs) const;
  bool operator!=(const AtlasTexture& rhs) const;

  void updateAnimation(void);
private:
  //Literally every private member here is used for animation 
  int currentFrame;
  int numFrames;

  int frameWidth;
  int frameHeight;

  int offsetX;
  int offsetY;
  int atlasWidth;
  int atlasHeight;
  //ms
  int frameStartTime;
  int frameDuration;

  GLfloat textureCoordinates[12];

  //Helper functions used by update animation
  GLfloat getLeftX();
  GLfloat getRightX();
  GLfloat getTopY();
  GLfloat getBottomY();
};


#endif
