--Sides
enum Side
{
   Side_Top;
   Side_Bottom;
   Side_Left;
   Side_Right
};

--[Tile_Platform]
character = "_";

--[Collision]
Sides
{
	Side_Top;
}

Lethal = false;

--[Kill_From]
KillSides
{
}

--[Components]
RigidBody = true;
BoxCollider = true;



