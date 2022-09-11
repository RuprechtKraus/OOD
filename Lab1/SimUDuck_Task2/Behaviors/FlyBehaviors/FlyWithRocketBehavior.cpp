#include "FlyWithRocketBehavior.h"
#include <iostream>
#include <format>

void FlyWithRocketBehavior::Fly() noexcept
{
	std::cout << std::format("I'm flying with rocket for the {}th time!!", ++m_flyCount) << std::endl;
}