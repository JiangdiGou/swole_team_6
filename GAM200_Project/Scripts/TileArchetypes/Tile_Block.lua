--Sides
SideTypes = 
{
   Side_Top = 0;
   Side_Right = 1;
   Side_Left = 2;
   Side_Bottom = 3;
}

--[Tile_Block]
character = "2";

--[Collision]
Sides =
{
	Side_Top, Side_Bottom, Side_Left, Side_Right;
}

Lethal = false;

--[Kill_From]
KillSides = 
{
}

--[Components]
RigidBody = true;
BoxCollider = true;

