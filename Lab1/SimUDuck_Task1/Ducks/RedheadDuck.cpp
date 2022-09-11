#include "RedheadDuck.h"
#include "Behaviors/DanceBehaviors/MinuetDanceBehavior.h"
#include "Behaviors/FlyBehaviors/FlyWithWingsBehavior.h"
#include "Behaviors/QuackBehaviors/QuackBehavior.h"
#include <iostream>

RedheadDuck::RedheadDuck()
	: Duck(std::make_unique<FlyWithWingsBehavior>(),
		std::make_unique<QuackBehavior>(),
		std::make_unique<MinuetDanceBehavior>())
{
}

void RedheadDuck::Display() const noexcept
{
	std::cout << "I'm redhead duck" << std::endl;
}