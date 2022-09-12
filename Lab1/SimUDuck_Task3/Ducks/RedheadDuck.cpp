#include "RedheadDuck.h"
#include "Behaviors/DanceBehavior.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include <iostream>

RedheadDuck::RedheadDuck()
	: Duck(GetFlyWithWingsBehavior(), NormalQuack, DanceMinuet)
{
}

void RedheadDuck::Display() const noexcept
{
	std::cout << "I'm redhead duck" << std::endl;
}