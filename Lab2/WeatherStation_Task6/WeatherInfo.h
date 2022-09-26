#pragma once
#include <limits>

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

struct WindInfo
{
	double speed = 0.0;
	double direction = NaN;
};

struct WeatherInfo
{
	double temperature = 0.0;
	double humidity = 0.0;
	double pressure = 0.0;
	WindInfo windInfo;
};