#ifndef LUATRANSLATE_H
#define LUATRANSLATE_H

#include "luaRunner.h"
#include "../gameComponents/Tile.h"

enum SideTypes {SIDE_TOP = 0, SIDE_RIGHT = 1, SIDE_LEFT = 2, SIDE_BOTTOM = 3};

class luaTranslate
{
public:
  luaTranslate();
  Tile *luaToTile(std::string fileName);

private:
  luaRunner interpret;
};

#endif