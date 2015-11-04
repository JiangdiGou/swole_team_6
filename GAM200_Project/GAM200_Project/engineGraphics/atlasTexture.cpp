#include "atlasTexture.h"

AtlasTexture::AtlasTexture(int aWidth, int aHeight, int numberOfFrames,
  int frameTime, int xOffset, int yOffset, int textureWidth, int textureHeight)
{
  //All this does is set members in obvious ways that dont warrant explaining
  numFrames = numberOfFrames;

  atlasWidth = aWidth;
  atlasHeight = aHeight;

  frameWidth = textureWidth / numberOfFrames;
  frameHeight = textureHeight; 

  currentFrame = 0;
  frameDuration = frameTime;

  offsetX = xOffset;
  offsetY = yOffset;

  frameStartTime = GetTickCount();

  textureCoordinates[0] = getRightX();
  textureCoordinates[1] = getBottomY();
  textureCoordinates[2] = getLeftX();
  textureCoordinates[3] = getTopY();
  textureCoordinates[4] = getLeftX();
  textureCoordinates[5] = getBottomY();
  textureCoordinates[6] = getRightX();
  textureCoordinates[7] = getBottomY();
  textureCoordinates[8] = getRightX();
  textureCoordinates[9] = getTopY();
  textureCoordinates[10] = getLeftX();
  textureCoordinates[11] = getTopY();
}

//**********************
//Function    : AtlasTexture.getBottomY
//Input       : none
//Output      : GLfloat - the Y coordinate of the bottom of the texture frame
//Description : Gets the Y coordinate of the bottom of the texture frame 
//**********************
GLfloat AtlasTexture::getBottomY()
{
  return ((float)offsetY + (float)frameHeight) / (float)atlasHeight;
}

//**********************
//Function    : Texture.getTopY
//Input       : none
//Output      : GLfloat - the Y coordinate of the top of the texture frame
//Description : Gets the Y coordinate of the top of the texture frame 
//**********************
GLfloat AtlasTexture::getTopY()
{
  return (float)offsetY / (float)atlasHeight;
}

//**********************
//Function    : Texture.getLeftX
//Input       : none
//Output      : GLfloat - the X coordinate of the left of the texture frame
//Description : Gets the X coordinate of the left of the texture frame 
//**********************
GLfloat AtlasTexture::getLeftX()
{
  return ((float)(currentFrame * frameWidth) + offsetX) / ((float)atlasWidth);
}

//**********************
//Function    : AtlasTexture.getRightX
//Input       : none
//Output      : GLfloat - the X coordinate of the right of the texture frame
//Description : Gets the X coordinate of the right of the texture frame 
//**********************
GLfloat AtlasTexture::getRightX()
{
  return ((float)(currentFrame * frameWidth) + offsetX + frameWidth) / ((float)atlasWidth);
}

void AtlasTexture::updateAnimation()
{
  //Calculate how long this frame has been going for 
  float deltaTime = GetTickCount() - frameStartTime;

  //If the frame has been going for longer tha nthe frame duration
  if (deltaTime > frameDuration)
  {
    //Check if it's at the end of the animation 
    if (currentFrame == (numFrames - 1))
      currentFrame = 0;
    else
      ++currentFrame;

    frameStartTime = GetTickCount();
  }

  //updates texture coordinates 
  textureCoordinates[0] = getRightX();
  textureCoordinates[1] = getBottomY();
  textureCoordinates[2] = getLeftX();
  textureCoordinates[3] = getTopY();
  textureCoordinates[4] = getLeftX();
  textureCoordinates[5] = getBottomY();
  textureCoordinates[6] = getRightX();
  textureCoordinates[7] = getBottomY();
  textureCoordinates[8] = getRightX();
  textureCoordinates[9] = getTopY();
  textureCoordinates[10] = getLeftX();
  textureCoordinates[11] = getTopY();
}

AtlasTexture::AtlasTexture()
{

}

bool AtlasTexture::operator==(const AtlasTexture& rhs) const
{
  //Offset should be unique for each texture in atlas
  //Also, if tex coords like W and H are used to crop, 
  //then those might vary. So offset is fine and sufficent anyway.
  if (offsetX == rhs.offsetX && offsetY == rhs.offsetY)
    return true;
}

bool AtlasTexture::operator!=(const AtlasTexture& rhs) const
{
  //Offset should be unique for each texture in atlas
  //Also, if tex coords like W and H are used to crop, 
  //then those might vary. So offset is fine and sufficent anyway.
  if (offsetX != rhs.offsetX || offsetY != rhs.offsetY)
    return true;
}


