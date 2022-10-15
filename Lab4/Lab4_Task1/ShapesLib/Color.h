#pragma once
#include <stdexcept>
#include <string>
#include "Utils/StringUtils.h"

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

static std::string ColorToString(Color color)
{
	switch (color)
	{
	case Color::Green:
		return "Green";
	case Color::Red:
		return "Red";
	case Color::Blue:
		return "Blue";
	case Color::Yellow:
		return "Yellow";
	case Color::Pink:
		return "Pink";
	case Color::Black:
		return "Black";
	default:
		throw std::invalid_argument("Unknown color");
	}
}

static Color StringToColor(const std::string& str)
{
	std::string copyStr(StringUtils::ToLower(str));

	if (copyStr == "green")
	{
		return Color::Green;
	}
	else if (copyStr == "red")
	{
		return Color::Red;
	}
	else if (copyStr == "blue")
	{
		return Color::Blue;
	}
	else if (copyStr == "yellow")
	{
		return Color::Yellow;
	}
	else if (copyStr == "pink")
	{
		return Color::Pink;
	}
	else if (copyStr == "black")
	{
		return Color::Black;
	}
	else
	{
		throw std::invalid_argument("Unknown color");
	}
}