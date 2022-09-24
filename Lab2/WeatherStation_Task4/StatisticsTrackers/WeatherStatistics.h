#pragma once
#include "WeatherInfo.h"
#include "ValueStatistics.h"

class WeatherStatistics
{
public:
	WeatherStatistics();
	void Update(const WeatherInfo& weatherInfo) noexcept;
	void Display() const noexcept;

private:
	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
};