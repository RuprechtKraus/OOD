#pragma once
#include <functional>
#include <iostream>
#include <format>

using FlyBehavior = std::function<void()>;

inline FlyBehavior GetFlyWithWingsBehavior()
{
	return [flyCount = 0]() mutable {
		std::cout << std::format("I'm flying with wings for the {}th time!!", ++flyCount) << std::endl;
	};
}

inline FlyBehavior GetFlyWithRocketBehavior()
{
	return [flyCount = 0]() mutable {
		std::cout << std::format("I'm flying on rocket for the {}th time!!", ++flyCount) << std::endl;
	};
}