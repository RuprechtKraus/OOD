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
		switch (m_size)
		{
		case MilkshakeSize::Small:
			return 50;
		case MilkshakeSize::Medium:
			return 60;
		case MilkshakeSize::Large:
			return 80;
		default:
			return 80;
		}
	}

private:
	MilkshakeSize m_size;
};
