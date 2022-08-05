#include "DecoyDuck.h"

DecoyDuck::DecoyDuck() noexcept
	: Duck(nullptr, nullptr, nullptr)
{
}

void DecoyDuck::Display() const noexcept
{
	std::cout << "I'm decoy duck" << std::endl;
}