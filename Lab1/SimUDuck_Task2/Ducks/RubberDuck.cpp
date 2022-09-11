#include "RubberDuck.h"
#include "Behaviors/DanceBehaviors/NoDanceBehavior.h"
#include "Behaviors/FlyBehaviors/NoFlyBehavior.h"
#include "Behaviors/QuackBehaviors/SqueakBehavior.h"
#include <iostream>

RubberDuck::RubberDuck()
	: Duck(std::make_unique<NoFlyBehavior>(),
		std::make_unique<SqueakBehavior>(),
		std::make_unique<NoDanceBehavior>())
{
}

void RubberDuck::Display() const noexcept
{
	std::cout << "I'm rubber duck" << std::endl;
}