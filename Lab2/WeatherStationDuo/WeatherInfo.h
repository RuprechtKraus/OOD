#pragma once
#include <optional>

struct WindInfo
{
	double speed = 0;
	double direction = 0;
};

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	WindInfo windInfo;
};