#pragma once

namespace ActionSystem
{
	namespace Internal
	{
		class ActionBase
		{
		public:
			void Pause() { Paused = true; }
			void Resume() { Paused = false; }
			bool IsPaused() const { return Paused; };
			bool IsCompleted() const{ return Completed; };

			virtual void Update(const long double& dt) = 0;

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