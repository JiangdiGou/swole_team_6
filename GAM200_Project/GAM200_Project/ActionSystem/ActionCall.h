#pragma once
#include "ActionBase.h"
#include <functional>

class ActionBase;

namespace ActionSystem
{
	class ActionCall : public ActionBase
	{
	public:
		ActionCall(const std::function<void(void)>& function) : Function(function){};
		
		template <typename ClassType>
		ActionCall(void (ClassType::*function)(void), ClassType* thisPtr) : Function(std::bind(function, thisPtr)) {};

		void ActionUpdate(const long double& dt) override;

		void Update(float dt) override;//stupid

	private:
		const std::function<void()> Function;
	};
}