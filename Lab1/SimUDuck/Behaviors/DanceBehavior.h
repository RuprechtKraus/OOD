#pragma once
#include <functional>
#include <iostream>

using DanceBehavior = std::function<void()>;

inline void DanceWaltz()
{
	std::cout << "I'm dancing waltz" << std::endl;
}

inline void DanceMinuet()
{
	std::cout << "I'm dancing minuet" << std::endl;
}