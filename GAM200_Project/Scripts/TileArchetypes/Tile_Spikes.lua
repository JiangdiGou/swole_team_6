--Sides
SideTypes = 
{
   Side_Top = 0;
   Side_Right = 1;
   Side_Left = 2;
   Side_Bottom = 3;
}

--[Tile_Spikes]
character = "^";

--[Collision]
Sides =
{
	Side_Top;
}

Lethal = true;

--[Kill_From]
KillSides =
{
	Side_Top;
}

--[Components]
RigidBody = true;
BoxCollider = true;
