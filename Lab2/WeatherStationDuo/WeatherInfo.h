#pragma once
#include <optional>

struct WindInfo
{
	double speed = 0;
	double direction = std::numeric_limits<double>::quiet_NaN();
};

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::optional<WindInfo> windInfo;
};