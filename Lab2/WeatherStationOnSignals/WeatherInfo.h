#pragma once
#include "WeatherEvent.h"
#include "WeatherStationLocation.h"
#include <limits>
#include <string>
#include <variant>

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

struct WindInfo
{
	double speed = NaN;
	double direction = NaN;
};

struct WeatherInfo
{
	std::variant<double, WindInfo> value;
	std::string valueName;
	std::string sourceName;
	StationType sourceLocation;
	WeatherEvent event;
};
