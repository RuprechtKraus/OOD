#include "MallardDuck.h"
#include "Behaviors/DanceBehaviors/WaltzDanceBehavior.h"
#include "Behaviors/FlyBehaviors/FlyWithWingsBehavior.h"
#include "Behaviors/QuackBehaviors/QuackBehavior.h"
#include <iostream>

MallardDuck::MallardDuck()
	: Duck(std::make_unique<FlyWithWingsBehavior>(),
		std::make_unique<QuackBehavior>(), 
		std::make_unique<WaltzDanceBehavior>())
{
}

void MallardDuck::Display() const noexcept
{
	std::cout << "I'm mallard duck" << std::endl;
}