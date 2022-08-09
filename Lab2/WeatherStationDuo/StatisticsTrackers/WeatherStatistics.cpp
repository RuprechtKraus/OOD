#include "WeatherStatistics.h"

void WeatherStatistics::AddData(const WeatherInfo& weatherInfo) noexcept
{
	m_temperature.AddEntry(weatherInfo.temperature);
	m_humidity.AddEntry(weatherInfo.humidity);
	m_pressure.AddEntry(weatherInfo.pressure);
	if (weatherInfo.windInfo)
	{
		m_wind.emplace(weatherInfo.windInfo.value());
	}
}

void WeatherStatistics::Display() const noexcept
{
	m_temperature.Display();
	m_humidity.Display();
	m_pressure.Display();
	if (m_wind)
	{
		m_wind.value().Display();
	}
}

WeatherStatistics::WindStatistics::WindStatistics(const WindInfo& windInfo)
{
	m_windSpeed.AddEntry(windInfo.speed);
	m_windDirection.AddEntry(windInfo);
}

void WeatherStatistics::WindStatistics::Display() const noexcept
{
	m_windSpeed.Display();
	m_windDirection.Display();
}