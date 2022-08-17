#pragma once
#include "WeatherData.h"
#include <vector>

class IWeatherDisplay
{
public:
	virtual void AddDataSource(IWeatherStation& wd, WeatherEvent events, double priority) = 0;
	virtual void RemoveDataSource(IWeatherStation& wd) = 0;
	virtual void Update(IWeatherStation* source, const WeatherInfo& info) = 0;
};