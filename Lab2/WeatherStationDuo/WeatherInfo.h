#pragma once
#include "WeatherEvents.h"
#include "WeatherStationLocation.h"
#include <limits>

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

struct WeatherInfo
{
	double temperature = NaN;
	double humidity = NaN;
	double pressure = NaN;
	double windSpeed = NaN;
	double windDirection = NaN;
	WeatherStationLocation sourceLocation;
	WeatherEvents events = static_cast<WeatherEvents>(0);
};

struct WindInfo
{
	double speed = NaN;
	double direction = NaN;
};