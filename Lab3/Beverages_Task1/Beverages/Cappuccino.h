#pragma once
#include "Coffee.h"

class Cappuccino : public Coffee
{
public:
	Cappuccino()
		: Coffee("Cappuccino")
	{
	}

	Cappuccino(const std::string& description)
		: Coffee(description)
	{
	}

	double GetCost() const noexcept override
	{
		return 80;
	}
};

class DoubleCappuccino : public Coffee
{
public:
	DoubleCappuccino()
		: Coffee("Double Cappuccino")
	{
	}

	double GetCost() const noexcept override
	{
		return 120;
	}
};