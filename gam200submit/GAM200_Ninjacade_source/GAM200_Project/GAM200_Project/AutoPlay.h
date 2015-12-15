/******************************************************************************/
/*!
\author Jiangdi Gou
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

#ifndef AUTOPLAY_H
#define AUTOPLAY_H

#include "Composition.h"
#include "Zilch/BindInternal.hpp"
#include "Zilch/Zilch.hpp"
#include "Core.h"


class AutoPlay : public GameComponent
{
    public: 
		
		AutoPlay();
		void Initialize()override;
		bool AutoPlayOn;
        //void SendMessages(Message*)override;
		void Update(float dt)override;
};

#endif