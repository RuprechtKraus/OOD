#include "ModelDuck.h"
#include "Behaviors/DanceBehavior.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include <iostream>

ModelDuck::ModelDuck()
	: Duck(nullptr, NormalQuack, nullptr)
{
}

void ModelDuck::Display() const noexcept
{
	std::cout << "I'm model duck" << std::endl;
}