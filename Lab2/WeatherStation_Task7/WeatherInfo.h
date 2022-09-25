#pragma once
#include "WeatherEvent.h"
#include <limits>
#include <string>
#include <variant>

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

struct WindInfo
{
	double speed = 0.0;
	double direction = NaN;
};

struct WeatherInfo
{
	WeatherEvent event;
	std::string valueName;
	std::variant<double, WindInfo> value;
};