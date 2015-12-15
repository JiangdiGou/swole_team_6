/******************************************************************************/
/*!
\author Jiangdi Gou
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/


#include "AutoPlay.h"
#include "Core.h"
#include <string>
//#include <cstdlib>
#include "WindowsSystem.h"


AutoPlay::AutoPlay() :AutoPlayOn(false)
{

}

void AutoPlay::Initialize()
{
	

}

void AutoPlay::Update(float dt)
{

	if (AutoPlayOn == true)
	{	
		MessageCharacterKey keyMsg;

		static char randominput[] = { 'W', 'S', 'D', 'A'};

	
		srand(time(0));

		int rand_index = rand() % 4;
		keyMsg.character = randominput[rand_index];
		std::cout << randominput[rand_index] << std::endl;
      
		CORE->BroadcastMessage(&keyMsg);
	}
	else if (AutoPlayOn == false)
	{
		return;
	}


}

