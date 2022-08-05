#include "RedheadDuck.h"

RedheadDuck::RedheadDuck() noexcept
	: Duck(FlyWithWings, NormalQuack, DanceMinuet)
{
}

void RedheadDuck::Display() const noexcept
{
	std::cout << "I'm redhead duck" << std::endl;
}