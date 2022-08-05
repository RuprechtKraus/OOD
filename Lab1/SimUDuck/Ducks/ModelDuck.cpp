#include "ModelDuck.h"

ModelDuck::ModelDuck() noexcept
	: Duck(nullptr, NormalQuack, nullptr)
{
}

void ModelDuck::Display() const noexcept
{
	std::cout << "I'm model duck" << std::endl;
}