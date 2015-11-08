--Editor Info
aType = {
	name = "Platform"	
}

--Sides
SideTypes = 
{
   Side_Top = 0;
   Side_Right = 1;
   Side_Left = 2;
   Side_Bottom = 3;
}

--[Tile_Platform]
character = "_";

--[Collision]
Sides =
{
	SideTypes.Side_Top;
}

Lethal = false;

--[Kill_From]
KillSides =
{
}

--[Components]
RigidBody = true;
BoxCollider = true;



