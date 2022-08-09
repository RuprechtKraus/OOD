#include "WeatherStatistics.h"

void WeatherStatistics::AddData(const WeatherInfo& weatherInfo) noexcept
{
	m_temperature.AddEntry(weatherInfo.temperature);
	m_humidity.AddEntry(weatherInfo.humidity);
	m_pressure.AddEntry(weatherInfo.pressure);
	m_windSpeed.AddEntry(weatherInfo.windInfo.speed);
	m_windDirection.AddEntry(weatherInfo.windInfo);
}

void WeatherStatistics::Display() const noexcept
{
	m_temperature.Display();
	m_humidity.Display();
	m_pressure.Display();
	m_windSpeed.Display();
	m_windDirection.Display();
}