--[Enemy Pathing Script]

-- takes two arrays of an x,y,z position for an enemy and the player
-- returns an array of the enemy's new x,y,z position
function newEnemyPos (playerPos, enemyPos)

	local newPos = {}
	
	-- gets the midpoint of the players positions[(pX - eX)/2, (pY - eY)/2, eZ] 
	newPos = {(playerPos[1] - enemyPos[1]) / 2, (playerPos[2] - enemyPos[2]) / 2, enemyPos[3]}
	-- sets the new position of the enemy
	enemyPos = newPos
	
	return newPos;
end