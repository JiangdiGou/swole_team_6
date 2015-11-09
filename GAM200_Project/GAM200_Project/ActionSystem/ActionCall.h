#pragma once
#include "ActionBase.h"
#include <functional>

namespace ActionSystem
{
	class ActionCall : public Internal::ActionBase
	{
	public:
		ActionCall(const std::function<void(void)>& function) : Function(function){};
		
		template <typename ClassType>
		ActionCall(void (ClassType::*function)(void), ClassType* thisPtr) : Function(std::bind(function, thisPtr)) {};

		void Update(const long double& dt) override;


	private:
		const std::function<void()> Function;
	};
}