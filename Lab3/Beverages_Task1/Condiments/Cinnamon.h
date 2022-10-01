#pragma once
#include "CondimentDecorator.h"

class Cinnamon : public CondimentDecorator
{
public:
	Cinnamon(IBeveragePtr&& beverage)
		: CondimentDecorator(move(beverage))
	{
	}

protected:
	double GetCondimentCost() const noexcept override
	{
		return 20;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Cinnamon";
	}
};