--Sides
enum Side
{
   Side_Top;
   Side_Bottom;
   Side_Left;
   Side_Right
};

--[Tile_Background]
character = "1";

--[Collision]
Sides
{
}

Lethal = false;

--[Kill_From]
KillSides
{
}

--[Components]
RigidBody = false;
BoxCollider = false;

