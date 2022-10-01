#pragma once
#include "CondimentDecorator.h"

enum class LiquorType
{
	Nut,
	Chocolate
};

class Liquor : public CondimentDecorator
{
public:
	Liquor(IBeveragePtr&& beverage, LiquorType type)
		: CondimentDecorator(std::move(beverage))
		, m_type(type)
	{
	}

	double GetCondimentCost() const noexcept override
	{
		return 50;
	}

	std::string GetCondimentDescription() const noexcept override
	{
		return std::string(m_type == LiquorType::Nut ? "Nut" : "Chocolate") + " liquor";
	}

private:
	LiquorType m_type;
};