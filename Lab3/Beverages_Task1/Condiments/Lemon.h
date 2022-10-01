#pragma once
#include "CondimentDecorator.h"

class Lemon : public CondimentDecorator
{
public:
	Lemon(IBeveragePtr&& beverage, unsigned quantity = 1)
		: CondimentDecorator(move(beverage))
		, m_quantity(quantity)
	{
	}

protected:
	double GetCondimentCost() const noexcept override
	{
		return 10.0 * m_quantity;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Lemon x " + std::to_string(m_quantity);
	}

private:
	unsigned m_quantity;
};