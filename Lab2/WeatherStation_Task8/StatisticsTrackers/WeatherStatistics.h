#pragma once
#include "WeatherInfo.h"
#include "ValueStatistics.h"
#include "CardinalDirectionStatistics.h"

class WeatherStatistics
{
public:
	WeatherStatistics(WeatherStationType sourceType);
	void Update(const WeatherInfo& weatherInfo) noexcept;
	void Display() const noexcept;

private:
	WeatherStationType m_sourceType;
	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
	ValueStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
};