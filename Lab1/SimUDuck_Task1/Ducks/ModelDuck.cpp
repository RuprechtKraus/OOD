#include "ModelDuck.h"
#include "Behaviors/DanceBehaviors/NoDanceBehavior.h"
#include "Behaviors/FlyBehaviors/NoFlyBehavior.h"
#include "Behaviors/QuackBehaviors/QuackBehavior.h"
#include <iostream>

ModelDuck::ModelDuck()
	: Duck(std::make_unique<NoFlyBehavior>(),
		std::make_unique<QuackBehavior>(),
		std::make_unique<NoDanceBehavior>())
{
}

void ModelDuck::Display() const noexcept
{
	std::cout << "I'm model duck" << std::endl;
}