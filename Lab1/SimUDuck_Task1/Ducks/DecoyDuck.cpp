#include "DecoyDuck.h"
#include "Behaviors/DanceBehaviors/NoDanceBehavior.h"
#include "Behaviors/FlyBehaviors/NoFlyBehavior.h"
#include "Behaviors/QuackBehaviors/MuteQuackBehavior.h"
#include <iostream>

DecoyDuck::DecoyDuck()
	: Duck(std::make_unique<NoFlyBehavior>(),
		std::make_unique<MuteQuackBehavior>(),
		std::make_unique<NoDanceBehavior>())
{
}

void DecoyDuck::Display() const noexcept
{
	std::cout << "I'm decoy duck" << std::endl;
}