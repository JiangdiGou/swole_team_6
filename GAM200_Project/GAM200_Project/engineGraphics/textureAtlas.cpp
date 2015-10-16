#define _CRT_SECURE_NO_WARNINGS //strcopy is unsafe
#include "textureAtlas.h"
#include <fstream>
#include <string>

void TextureAtlas::parseTextureList(const char* filename)
{
  std::string infoString;
  std::vector<std::string> tokens;
  std::string::iterator stringIt;
  char* pToken;

  //Tries to open the file
  std::ifstream atlas(filename);
  //If successfully opened
  if (atlas.is_open())
  {
    //Reads the file line by line
    while (getline(atlas, infoString))
    {
      //If theres any sort of error, print out error msg.
      if (atlas.fail())
      {
        std::cout << "Error reading " << filename << std::endl;
      }
      else
      {
        //Copies the Line we just go into a Cstr so I can use strtok on it 
        char* cStr = new char[infoString.size() + 1];
        std::strcpy(cStr, infoString.data());
        pToken = std::strtok(cStr, " _=");
        //Tokenizes the string, the string is destroyed in process
        while (pToken != NULL)
        {
          //Pushes the tokens into a vector
          tokens.push_back(std::string(pToken));
          pToken = std::strtok(NULL, " _=");
        }
        
        //Generates a new AtlasTexture based on the tokens we got from file 
        AtlasTexture newTexture = AtlasTexture(width, height, std::stoi(tokens[1]),
          84, std::stoi(tokens[2]), std::stoi(tokens[3]), std::stoi(tokens[4]),
          std::stoi(tokens[5]));
        
        //Adds this AtlasTexture to map 
        textures.insert(std::pair<std::string, AtlasTexture>(
          tokens[0], newTexture));

        tokens.clear();
        delete[] cStr;
      }
    }
  }
  else
    std::cout << "Failed to open " << filename << std::endl;
}

TextureAtlas::TextureAtlas(const char* atlasname, const char* tListName)
{
  int textureWidth, textureHeight;

  //Generates the Texture ID and stores in var 
  glGenTextures(1, &ID);

  //Binds the texture so future fx calls will affect this texture
  glBindTexture(GL_TEXTURE_2D, ID);

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

  parseTextureList(tListName);
}

void TextureAtlas::debugMap()
{
  typedef std::map<std::string, AtlasTexture>::iterator it_type;
  for (it_type iterator = textures.begin(); iterator != textures.end(); iterator++)
  {
    std::cout << "Displaying tex coords for " << iterator->first << std::endl;
    (iterator->second).updateAnimation();
    for (int i = 0; i < 12; i+=2)
    {
      std::cout << "(" << iterator->second.textureCoordinates[i];
      std::cout << ", " << iterator->second.textureCoordinates[i + 1];
      std::cout << ")" << std::endl;
    }

  }
}

TextureAtlas::TextureAtlas()
{

}