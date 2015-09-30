--Sides
enum Side
{
   Side_Top;
   Side_Bottom;
   Side_Left;
   Side_Right
};

--[Tile_Block]
character = "2";

--[Collision]
Sides
{
	Side_Top, Side_Bottom, Side_Left, Side_Right;
}

Lethal = false;

--[Kill_From]
KillSides
{
}

--[Components]
RigidBody = true;
BoxCollider = true;

