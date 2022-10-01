#pragma once
#include "CondimentDecorator.h"

class ChocolateCrumbs : public CondimentDecorator
{
public:
	ChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
		: CondimentDecorator(move(beverage))
		, m_mass(mass)
	{
	}

	double GetCondimentCost() const noexcept override
	{
		return 2.0 * m_mass;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Chocolate crumbs " + std::to_string(m_mass) + "g";
	}

private:
	unsigned m_mass;
};