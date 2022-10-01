#pragma once
#include "CondimentDecorator.h"

class CoconutFlakes : public CondimentDecorator
{
public:
	CoconutFlakes(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

	double GetCondimentCost() const noexcept override
	{
		return 1.0 * m_mass;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Coconut flakes " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};