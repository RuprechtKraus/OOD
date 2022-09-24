#pragma once
#include "WeatherStationType.h"

struct WeatherInfo
{
	WeatherStationType stationType;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};