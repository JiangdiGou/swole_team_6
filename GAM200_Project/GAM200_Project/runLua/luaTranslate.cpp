//author Nolan Yoo

#include "luaRunner.h"
#include "luaTranslate.h"

luaTranslate::luaTranslate()
{
  this->interpret = *new luaRunner();
}

Tile *luaTranslate::luaToTile(std::string fileName)
{
  this->interpret.loadFile(fileName);
  Tile *archetype = new Tile();

  archetype->character = this->interpret.get<char>("character");
  archetype->lethal = this->interpret.get<bool>("lethal");

  return archetype;
}