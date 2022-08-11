#pragma once
#include "WeatherEvent.h"
#include "WeatherStationLocation.h"
#include <limits>
#include <string>

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

struct WeatherInfo
{
	double value;
	std::string valueName;
	std::string sourceName;
	StationType sourceLocation;
};

struct WindInfo
{
	double speed = NaN;
	double direction = NaN;
};