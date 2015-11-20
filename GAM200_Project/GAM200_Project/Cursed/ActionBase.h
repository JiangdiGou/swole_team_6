#pragma once

//#include "../Engine.h"
#include "ActionMath.h"
namespace ActionSystem
{
		class ActionBase //: public ISystem
		{
		public:
			void Pause() { Paused = true; }
			void Resume() { Paused = false; }
			bool IsPaused() const { return Paused; };
			bool IsCompleted() const{ return Completed; };

			virtual void ActionUpdate(const long double& dt) = 0;

			virtual void Update(float dt) = 0;//comment this out

			virtual void Restart() { Completed = false; }

			virtual ~ActionBase(){};

			//This class is always the main class, therfore it's protected
		protected:
			bool Paused = false;
			bool Completed = false;

			ActionBase(){}; 
		};
}// namespace Action System