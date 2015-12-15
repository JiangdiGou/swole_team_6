/******************************************************************************/
/*!
\author Nolan Yoo
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#include "luaRunner.h"
#include "luaTranslate.h"
#include <vector>
#include "../multiType.h"

luaTranslate::luaTranslate()
{
  this->interpret = *new luaRunner();
}

Tile *luaTranslate::luaToTile(std::string fileName)
{
  this->interpret.loadFile(fileName);
  Tile *archetype = new Tile();

  archetype->character = this->interpret.get<char>("character");
  archetype->lethal = this->interpret.get<bool>("Lethal");
  archetype->hasRigidBody = this->interpret.get<bool>("RigidBody");
  archetype->hasBoxCollider = this->interpret.get<bool>("BoxCollider");

  std::vector<multiType> sides = this->interpret.getTable("Sides");
  std::vector<multiType> killSides = this->interpret.getTable("KillSides");

  for ( auto i = sides.begin(); i != sides.end(); i++ ) {
    archetype->sides[i->integer] = true;
  }

  for ( auto i = killSides.begin(); i != killSides.end(); i++ ) {
    archetype->killSides[i->integer] = true;
  }

  return archetype;
}