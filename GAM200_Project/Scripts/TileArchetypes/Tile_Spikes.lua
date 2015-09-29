--[Tile_Spikes]
character = "^";

--[Collision]
Sides()
{
	top;
}

Lethal = true;

--[Kill_From]
KillSides
{
	top;
}

--[Components]
RigidBody = true;
BoxCollider = true;
