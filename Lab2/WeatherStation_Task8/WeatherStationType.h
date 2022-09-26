#pragma once
#include <stdexcept>
#include <string>

enum class WeatherStationType
{
	INSIDE,
	OUTSIDE
};

static std::string WeatherStationTypeToString(WeatherStationType type)
{
	switch (type)
	{
	case WeatherStationType::INSIDE:
		return "INSIDE";
	case WeatherStationType::OUTSIDE:
		return "OUTSIDE";
	default:
		throw std::logic_error("Unknown weather station type");
	}
}