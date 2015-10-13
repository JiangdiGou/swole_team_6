//STUFF
#define _CRT_SECURE_NO_WARNINGS
#include "textureAtlas.h"
//C style cause it has a tokenize function i want. 
#include <fstream>
#include <string>

void TextureAtlas::parseTextureList(const char* filename)
{

  std::string infoString, subString;
  std::vector<std::string> tokens;
  char * info;
  std::string::iterator stringIt, substringStart;
  int subStrStart = 0, subStrLen = 0;
  std::cout << "Trying to parse" << std::endl;
  char* pToken;

  std::ifstream atlas(filename);
  if (atlas.is_open())
  {
    while (getline(atlas, infoString))
    {
      if (atlas.fail())
      {
        std::cout << "Error reading " << filename << std::endl;
      }
      else
      {
        char* cStr = new char[infoString.size() + 1];
        std::strcpy(cStr, infoString.data());
        pToken = std::strtok(cStr, " _=");
        while (pToken != NULL)
        {
          std::cout << pToken << std::endl;
          tokens.push_back(std::string(pToken));
          pToken = std::strtok(NULL, " _=");
        }

        
        textures.insert(std::pair<const char*, AtlasTexture>(
          tokens[0].data(),
          AtlasTexture(width, height, std::stoi(tokens[1]), 1000,
          std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]),
          std::stoi(tokens[5]))));
        tokens.clear();
        delete[] cStr;
        
      }
    }
  }
  else
    std::cout << "Failed to open " << filename << std::endl;
}

TextureAtlas::TextureAtlas(const char* atlasname)
{
  int textureWidth, textureHeight;
  GLuint texture;

  //Generates the Texture ID and stores in var 
  glGenTextures(1, &texture);

  //Binds the texture so future fx calls will affect this texture
  glBindTexture(GL_TEXTURE_2D, texture);

  //Loads the image using soil 
  unsigned char* image = SOIL_load_image(atlasname, &textureWidth,
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

  width = textureWidth;
  height = textureHeight;
}

void TextureAtlas::debugMap()
{

}