#pragma once
#include "ValueStatistics.h"
#include "WeatherData.h"

class WeatherStatistics
{
public:
	WeatherStatistics(std::ostream& output = std::cout);
	void AddEntry(const WeatherInfo& weatherInfo);
	void Display(WeatherEvent event) const noexcept;

private:
	void TryAddEntry(const WeatherInfo& weatherInfo);

	std::ostream& m_output;
	NumericStatistics m_temperature;
	NumericStatistics m_humidity;
	NumericStatistics m_pressure;
	NumericStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
	WeatherEvent m_events{ static_cast<WeatherEvent>(0) };
};