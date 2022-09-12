#include "RubberDuck.h"
#include "Behaviors/DanceBehavior.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include <iostream>

RubberDuck::RubberDuck()
	: Duck(nullptr, SqueakQuack, nullptr)
{
}

void RubberDuck::Display() const noexcept
{
	std::cout << "I'm rubber duck" << std::endl;
}