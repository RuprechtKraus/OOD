#pragma once
#include "CondimentDecorator.h"

class Cream : public CondimentDecorator
{
public:
	Cream(IBeveragePtr&& beverage)
		: CondimentDecorator(std::move(beverage))
	{
	}

	double GetCondimentCost() const noexcept override
	{
		return 25;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Cream";
	}
};