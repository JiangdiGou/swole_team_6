#include "Texture.h"

//**********************
//Function    : Texture
//Input       : none
//Output      : Texture - the constructed Texture
//Description : default constructor for texture, does nothing. 
//**********************
Texture::Texture()
{
}

//**********************
//Function    : ~Texture
//Input       : none
//Output      : none
//Description : destructor for texture, currently does nothing. 
//**********************
Texture::~Texture()
{
}

//**********************
//Function    : Texture
//Input       : filePath - the filename/path to the image file 
//Output      : Texture - the constructed Texture
//Description : Constructs a texture from an image file
//**********************
Texture::Texture(const char* filePath)
{
  int textureWidth, textureHeight;
  GLuint texture;

  //Generates the Texture ID and stores in var 
  glGenTextures(1, &texture);

  //Binds the texture so future fx calls will affect this texture
  glBindTexture(GL_TEXTURE_2D, texture);

  //Loads the image using soil 
  unsigned char* image = SOIL_load_image(filePath, &textureWidth,
    &textureHeight, 0, SOIL_LOAD_RGBA);

  //Generates Texture info 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);


  //Sets the Blending mode 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  //de allocates resources and unbinds texture 
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  ID = texture;
  numFrames = 1;
  currentFrame = 0;
  frameDuration = 0;
  numRows = 1;
  numColumns = 1;

  //Sets initial texture coords
  textureCoordinates[0] = 0.0f;
  textureCoordinates[1] = 1.0f;
  textureCoordinates[2] = 1.0f;
  textureCoordinates[3] = 0.0f;
  textureCoordinates[4] = 1.0f;
  textureCoordinates[5] = 1.0f;
  textureCoordinates[6] = 0.0f;
  textureCoordinates[7] = 1.0f;
  textureCoordinates[8] = 0.0f;
  textureCoordinates[9] = 0.0f;
  textureCoordinates[10] = 1.0f;
  textureCoordinates[11] = 0.0f;

  offsetXBytes = 0;
  offsetYBytes = 0;
}

//**********************
//Function    : Texture
//Input       : filePath       - the filename/path to the image file 
//              numberOfFrames - the amount of frames in an animation
//              frameWidth     - the width of a frame in pixels
//              frameHeight    - the height of a frame in pixels
//              frameTime      - the duration of a frame in milliseconds 
//Output      : Texture - the constructed Texture
//Description : Constructs an animated texture from a sprite sheet 
//**********************
Texture::Texture(const char* filePath, int numberOfFrames, int frameWidth, int frameHeight, float frameTime)
{
  int textureWidth, textureHeight;
  GLuint texture;

  //Generates the Texture ID and stores in var 
  glGenTextures(1, &texture);

  //Binds the texture so future fx calls will affect this texture
  glBindTexture(GL_TEXTURE_2D, texture);

  //Loads the image using soil 
  unsigned char* image = SOIL_load_image(filePath, &textureWidth,
    &textureHeight, 0, SOIL_LOAD_RGBA);

  //Generates Texture info 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,
    GL_RGBA, GL_UNSIGNED_BYTE, image);
  glGenerateMipmap(GL_TEXTURE_2D);

  //Sets the Blending mode 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  //de allocates resources and unbinds texture 
  SOIL_free_image_data(image);
  glBindTexture(GL_TEXTURE_2D, 0);

  //Calculates number of rows and columns
  numRows = textureHeight / frameHeight;
  numColumns = textureWidth / frameWidth;

  ID = texture;
  numFrames = numberOfFrames;
  currentFrame = 0;
  frameDuration = frameTime;
  frameStartTime = GetTickCount();
  
  //Sets the initial texture Coordinates 
  textureCoordinates[0] = 1.0f;
  textureCoordinates[1] = 0.0f;
  textureCoordinates[2] = 0.0f;
  textureCoordinates[3] = 1.0f;
  textureCoordinates[4] = 0.0f;
  textureCoordinates[5] = 0.0f;
  textureCoordinates[6] = 1.0f;
  textureCoordinates[7] = 0.0f;
  textureCoordinates[8] = 1.0f;
  textureCoordinates[9] = 1.0f;
  textureCoordinates[10] = 0.0f;
  textureCoordinates[11] = 1.0f;

  offsetXBytes = 0;
  offsetYBytes = 0;

  width = textureWidth;
  height = textureHeight;
}

//**********************
//Function    : Texture
//Input       : filePath       - the filename/path to the image file 
//              numberOfFrames - the amount of frames in an animation
//              frameWidth     - the width of a frame in pixels
//              frameHeight    - the height of a frame in pixels
//              frameTime      - the duration of a frame in milliseconds 
//				startOffsetX   - the offset in the atlas where this starts
//				startOffsetY   - the offset in the atlas where this starts
//Output      : Texture - the constructed Texture
//Description : Constructs an animated texture from a sprite sheet in an atlas 
//**********************
Texture::Texture(const char* filePath, int numberOfFrames, int frameWidth, int frameHeight, 
				float frameTime, int startOffsetX, int startOffsetY)
{
	int textureWidth, textureHeight;
	GLuint texture;

	//Generates the Texture ID and stores in var 
	glGenTextures(1, &texture);

	//Binds the texture so future fx calls will affect this texture
	glBindTexture(GL_TEXTURE_2D, texture);

	//Loads the image using soil 
	unsigned char* image = SOIL_load_image(filePath, &textureWidth,
		&textureHeight, 0, SOIL_LOAD_RGBA);

	//Generates Texture info 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Sets the Blending mode 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//de allocates resources and unbinds texture 
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Calculates number of rows and columns
	numRows = (textureHeight + startOffsetY) / frameHeight;
	numColumns = (textureWidth + startOffsetX) / frameWidth;

	ID = texture;
	numFrames = numberOfFrames;
	currentFrame = 0;
	frameDuration = frameTime;
	frameStartTime = GetTickCount();

	//Sets the initial texture Coordinates 
	textureCoordinates[0] = 1.0f;
	textureCoordinates[1] = 0.0f;
	textureCoordinates[2] = 0.0f;
	textureCoordinates[3] = 1.0f;
	textureCoordinates[4] = 0.0f;
	textureCoordinates[5] = 0.0f;
	textureCoordinates[6] = 1.0f;
	textureCoordinates[7] = 0.0f;
	textureCoordinates[8] = 1.0f;
	textureCoordinates[9] = 1.0f;
	textureCoordinates[10] = 0.0f;
	textureCoordinates[11] = 1.0f;

	offsetXBytes = startOffsetX;
	offsetYBytes = startOffsetY;

	width = textureWidth;
	height = textureHeight;
}

//**********************
//Function    : Texture.updateAnimation
//Input       : none
//Output      : none
//Description : Advances the textures frame if neessary and updates tex coords
//**********************
void Texture::updateAnimation()
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


//**********************
//Function    : Texture.getBottomY
//Input       : none
//Output      : GLfloat - the Y coordinate of the bottom of the texture frame
//Description : Gets the Y coordinate of the bottom of the texture frame 
//**********************
GLfloat Texture::getBottomY()
{
	return (((currentFrame / numColumns) + 1) * (1.0 / (float)numRows)) + ((float)offsetYBytes/height);
}

//**********************
//Function    : Texture.getTopY
//Input       : none
//Output      : GLfloat - the Y coordinate of the top of the texture frame
//Description : Gets the Y coordinate of the top of the texture frame 
//**********************
GLfloat Texture::getTopY()
{
	return ((currentFrame / numColumns) * (1.0 / (float)numRows)) + ((float)offsetYBytes / height);
}

//**********************
//Function    : Texture.getLeftX
//Input       : none
//Output      : GLfloat - the X coordinate of the left of the texture frame
//Description : Gets the X coordinate of the left of the texture frame 
//**********************
GLfloat Texture::getLeftX()
{
	return ((currentFrame % numColumns) * (1.0 / (float)numColumns)) + ((float)offsetXBytes / width);
}

//**********************
//Function    : Texture.getRightX
//Input       : none
//Output      : GLfloat - the X coordinate of the right of the texture frame
//Description : Gets the X coordinate of the right of the texture frame 
//**********************
GLfloat Texture::getRightX()
{
	return (((currentFrame % numColumns) + 1) * (1.0 / (float)numColumns)) + ((float)offsetXBytes / width);
}
