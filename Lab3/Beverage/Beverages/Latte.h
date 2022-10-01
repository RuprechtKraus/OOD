#pragma once
#include "Coffee.h"

class Latte : public Coffee
{
public:
	Latte()
		: Coffee("Latte")
	{
	}

	Latte(const std::string& description)
		: Coffee(description)
	{
	}

	double GetCost() const noexcept override
	{
		return 90;
	}
};

class DoubleLatte : public Latte
{
public:
	DoubleLatte()
		: Latte("Double Latte")
	{
	}

	double GetCost() const noexcept override
	{
		return 130;
	}
};