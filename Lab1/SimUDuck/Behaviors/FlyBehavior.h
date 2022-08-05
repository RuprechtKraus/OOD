#pragma once
#include <functional>
#include <iostream>

using FlyBehavior = std::function<void()>;

inline void FlyWithWings()
{
	std::cout << "I'm flying with wings!!!" << std::endl;
}

inline void FlyWithRocket()
{
	std::cout << "I'm flying on rocket!!!" << std::endl;
}