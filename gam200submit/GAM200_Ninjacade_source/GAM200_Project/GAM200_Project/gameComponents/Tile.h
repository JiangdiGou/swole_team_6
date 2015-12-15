#ifndef TILE_H
#define TILE_H

class Tile
{
public:
  char character;
  bool lethal;
  bool sides[4];
  bool killSides[4];

  bool hasRigidBody;
  bool hasBoxCollider;
};

#endif