#ifndef LUATRANSLATE_H
#define LUATRANSLATE_H

#include "luaRunner.h"
#include "../gameComponents/Tile.h"

class luaTranslate
{
public:
  luaTranslate();
  Tile *luaToTile(std::string fileName);

private:
  luaRunner interpret;
};

#endif