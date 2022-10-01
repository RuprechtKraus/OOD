#pragma once
#include "Beverages/IBeverage.h"

class CondimentDecorator : public IBeverage
{
public:
	std::string GetDescription() const noexcept override
	{
		return m_beverage->GetDescription() + ", " + GetCondimentDescription();
	}

	double GetCost() const noexcept override
	{
		return m_beverage->GetCost() + GetCondimentCost();
	}

protected:
	CondimentDecorator(IBeveragePtr&& beverage)
		: m_beverage(std::move(beverage))
	{
	}

	virtual std::string GetCondimentDescription() const = 0;
	virtual double GetCondimentCost() const = 0;

private:
	IBeveragePtr m_beverage;
};