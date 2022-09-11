#include "FlyWithWingsBehavior.h"
#include <format>
#include <iostream>

void FlyWithWingsBehavior::Fly()
{
	std::cout << std::format("I'm flying with wings for the {}th time!!", ++m_flyCount) << std::endl;
}