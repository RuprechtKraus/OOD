#pragma once
#include "CondimentDecorator.h"

enum class SyrupType
{
	Chocolate,
	Maple
};

class Syrup : public CondimentDecorator
{
public:
	Syrup(IBeveragePtr&& beverage, SyrupType syrupType)
		: CondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{
	}

	double GetCondimentCost() const noexcept override
	{
		return 15;
	}
	std::string GetCondimentDescription() const noexcept override
	{
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
			+ " syrup";
	}

private:
	SyrupType m_syrupType;
};