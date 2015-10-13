#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

//also stuff 
#include "AtlasTexture.h"
#include <map>


class TextureAtlas
{
public:
  const char* atlasFileName;

  TextureAtlas(const char* atlasname);
  void parseTextureList(const char* filename);
  GLuint ID;
  std::map<const char*, AtlasTexture> textures;

  float width, height;

  void debugMap();
};

#endif