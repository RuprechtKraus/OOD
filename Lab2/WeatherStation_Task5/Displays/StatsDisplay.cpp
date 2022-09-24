#include "StatsDisplay.h"

StatsDisplay::StatsDisplay()
	: m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
	, m_windSpeed("Wind Speed")
	, m_windDirection("Wind Direction")
{
}

void StatsDisplay::Update(WeatherInfo const& data)
{
	m_temperatureStats.Update(data.temperature);
	m_humidityStats.Update(data.humidity);
	m_pressureStats.Update(data.pressure);
	m_windSpeed.Update(data.windInfo.speed);
	m_windDirection.Update(data.windInfo);
	Display();
}

void StatsDisplay::Display() const noexcept
{
	m_temperatureStats.Display();
	m_humidityStats.Display();
	m_pressureStats.Display();
	m_windSpeed.Display();
	m_windDirection.Display();
}