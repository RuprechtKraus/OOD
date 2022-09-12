#include "MallardDuck.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include "Behaviors/DanceBehavior.h"
#include <iostream>

MallardDuck::MallardDuck()
	: Duck(GetFlyWithWingsBehavior(), NormalQuack, DanceWaltz)
{
}

void MallardDuck::Display() const noexcept
{
	std::cout << "I'm mallard duck" << std::endl;
}