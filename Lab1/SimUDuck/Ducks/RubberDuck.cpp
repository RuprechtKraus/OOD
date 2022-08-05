#include "RubberDuck.h"

RubberDuck::RubberDuck() noexcept
	: Duck(nullptr, SqueakQuack, nullptr)
{
}

void RubberDuck::Display() const noexcept
{
	std::cout << "I'm rubber duck" << std::endl;
}