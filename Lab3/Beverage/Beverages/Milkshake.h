#pragma once
#include "BeverageBase.h"
#include <stdexcept>

enum class MilkshakeSize
{
	Small,
	Medium,
	Large
};

static std::string MilkshakeSizeToString(MilkshakeSize size)
{
	switch (size)
	{
	case MilkshakeSize::Small:
		return "Small";
	case MilkshakeSize::Medium:
		return "Medium";
	case MilkshakeSize::Large:
		return "Large";
	default:
		throw std::invalid_argument("Unknown milkshake size");
	}
}

class Milkshake : public BeverageBase
{
public:
	Milkshake(MilkshakeSize size)
		: BeverageBase(MilkshakeSizeToString(size) + " Milkshake")
	{
	}

	double GetCost() const noexcept override
	{
		return 80;
	}
};
