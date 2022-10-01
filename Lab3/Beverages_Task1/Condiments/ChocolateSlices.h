#pragma once
#include "CondimentDecorator.h"
#include <stdexcept>

class ChocolateSlices : public CondimentDecorator
{
public:
	ChocolateSlices(IBeveragePtr&& beverage, unsigned quantity)
		: CondimentDecorator(std::move(beverage))
		, m_quantity(quantity)
	{
		if (m_quantity > MAX_SLICE_QUANTITY)
		{
			throw std::invalid_argument(
				"Max number of chocolate slices is " + std::to_string(MAX_SLICE_QUANTITY));
		}
	}

	double GetCondimentCost() const noexcept override
	{
		return 10.0 * m_quantity;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return "Chocolate slice x " + std::to_string(m_quantity);
	}

private:
	static const int MAX_SLICE_QUANTITY{ 5 };
	unsigned m_quantity;
};