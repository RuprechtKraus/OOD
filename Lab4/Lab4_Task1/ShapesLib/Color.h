#pragma once
#include <stdexcept>
#include <string>

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