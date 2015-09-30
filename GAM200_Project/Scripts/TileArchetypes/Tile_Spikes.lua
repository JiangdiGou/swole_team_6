--Sides
enum Side
{
   Side_Top;
   Side_Bottom;
   Side_Left;
   Side_Right
};

--[Tile_Spikes]
character = "^";

--[Collision]
Sides
{
	Side_Top;
}

Lethal = true;

--[Kill_From]
KillSides
{
	Side_Top;
}

--[Components]
RigidBody = true;
BoxCollider = true;
