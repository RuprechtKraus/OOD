#pragma once
#include "ValueStatistics.h"
#include "WeatherData.h"

class WeatherStatistics
{
public:
	WeatherStatistics(std::ostream& output = std::cout);
	void AddEntry(const WeatherInfo& weatherInfo) noexcept;
	void UpdateEvents(WeatherEvent newEvents) noexcept;
	void Display() const noexcept;

private:
	template <typename S, typename T>
	static void AddValueEntry(S& statistics, const T& value, WeatherEvent happendEvents, WeatherEvent requiredEvent);
	template <typename S>
	static void DisplayValue(S& statistics, WeatherEvent events, WeatherEvent targetEvent);

	std::ostream& m_output;
	NumericStatistics m_temperature;
	NumericStatistics m_humidity;
	NumericStatistics m_pressure;
	NumericStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
	WeatherEvent m_events{ static_cast<WeatherEvent>(0) };
};