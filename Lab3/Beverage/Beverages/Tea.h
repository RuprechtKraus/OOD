#pragma once
#include "BeverageBase.h"
#include <stdexcept>

enum class TeaType
{
	Black,
	Green,
	Hibiscus,
	Puer
};

static std::string TeaTypeToString(TeaType type)
{
	switch (type)
	{
	case TeaType::Black:
		return "Black";
	case TeaType::Green:
		return "Green";
	case TeaType::Hibiscus:
		return "Hibiscus";
	case TeaType::Puer:
		return "Puer";
	default:
		throw std::invalid_argument("Unknown tea type");
	}
}

class Tea : public BeverageBase
{
public:
	Tea(TeaType type)
		: BeverageBase(TeaTypeToString(type) + " tea")
	{
	}

	double GetCost() const noexcept override
	{
		return 30;
	}
};