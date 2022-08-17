#pragma once
#include "WeatherInfo.h"
#include <vector>

class IWeatherDisplay
{
public:
	virtual void Update(const WeatherInfo& info) = 0;
};