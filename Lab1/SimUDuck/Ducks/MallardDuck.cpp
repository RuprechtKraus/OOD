#include "MallardDuck.h"

MallardDuck::MallardDuck() noexcept
	: Duck(FlyWithWings, NormalQuack, DanceWaltz)
{
}

void MallardDuck::Display() const noexcept
{
	std::cout << "I'm mallard duck" << std::endl;
}