#pragma once

#include "../Engine.h"

namespace ActionSystem
{
	namespace Internal
	{
		class ActionBase : public ISystem
		{
		public:
			void Pause() { Paused = true; }
			void Resume() { Paused = false; }
			bool IsPaused() const { return Paused; };
			bool IsCompleted() const{ return Completed; };

			virtual void ActionUpdate(const long double& dt) = 0;

			//virtual void Update(float dt) override;//comment this out

			virtual void Restart() { Completed = false; }

			virtual ~ActionBase(){};

			//This class is always the main class, therfore it's protected
		protected:
			bool Paused = false;
			bool Completed = false;

			ActionBase(){};
		};
	}// namespace Internal
}// namespace Action System