#pragma once
#include "BeverageBase.h"

class Tea : public BeverageBase
{
public:
	Tea()
		: BeverageBase("Tea")
	{
	}

	Tea(const std::string& description)
		: BeverageBase(description)
	{
	}

	double GetCost() const noexcept override
	{
		return 30;
	}
};

class BlackTea : public Tea
{
public:
	BlackTea()
		: Tea("Black Tea")
	{
	}
};

class GreenTea : public Tea
{
public:
	GreenTea()
		: Tea("Green Tea")
	{
	}
};

class HibiscusTea : public Tea
{
public:
	HibiscusTea()
		: Tea("Hibiscus Tea")
	{
	}
};

class PuerTea : public Tea
{
public:
	PuerTea()
		: Tea("Pu'er tea")
	{
	}
};