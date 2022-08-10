#pragma once
#include "ValueStatistics.h"
#include "WeatherData.h"
#include <optional>

class WeatherStatistics
{
public:
	void AddData(const WeatherInfo& weatherInfo) noexcept;
	void Display() const noexcept;

private:
	NumericStatistics m_temperature{ "Temp" };
	NumericStatistics m_humidity{ "Hum" };
	NumericStatistics m_pressure{ "Pressure" };
	NumericStatistics m_windSpeed{ "Wind speed" };
	CardinalDirectionStatistics m_windDirection{ "Wind direction" };
};