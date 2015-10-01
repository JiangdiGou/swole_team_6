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
	SideTypes.Side_Top;
	SideTypes.Side_Right;
	SideTypes.Side_Left;
	SideTypes.Side_Bottom;
}

Lethal = false;

--[Kill_From]
KillSides = 
{
}

--[Components]
RigidBody = true;
BoxCollider = true;

