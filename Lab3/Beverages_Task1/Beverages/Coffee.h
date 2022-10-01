#pragma once
#include "BeverageBase.h"

class Coffee : public BeverageBase
{
public:
	Coffee(const std::string& description = "Coffee")
		: BeverageBase(description)
	{
	}

	double GetCost() const noexcept override
	{
		return 60;
	}
};