#include "DecoyDuck.h"
#include "Behaviors/DanceBehavior.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include <iostream>

DecoyDuck::DecoyDuck()
	: Duck(nullptr, nullptr, nullptr)
{
}

void DecoyDuck::Display() const noexcept
{
	std::cout << "I'm decoy duck" << std::endl;
}