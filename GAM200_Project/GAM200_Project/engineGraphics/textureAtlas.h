#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

//also stuff 
#include "AtlasTexture.h"
#include <map>


class TextureAtlas
{
public:
  //Constructor from a filename, what should be used. 
  TextureAtlas(const char* atlasname, const char* tListName);
  //It needs adefault constructor for reasons. But it doesnt do anything. 
  TextureAtlas();
  //Actual openGL texture ID 
  GLuint ID;
  //Map storing all its inner textures 
  std::map<std::string, AtlasTexture> textures;
  //W and H needed for animation to convert shit to tex coords 
  float width, height;
  //Prints out all info about atlasTextures in the map 
  void debugMap();
private:
  //parses a texture list file to populate the map
  void parseTextureList(const char* filename);

};

#endif