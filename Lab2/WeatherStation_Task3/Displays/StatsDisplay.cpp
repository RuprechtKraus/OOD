#include "StatsDisplay.h"

StatsDisplay::StatsDisplay()
	: m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
{
}

void StatsDisplay::Update(WeatherInfo const& data)
{
	m_temperatureStats.Update(data.temperature);
	m_humidityStats.Update(data.humidity);
	m_pressureStats.Update(data.pressure);
	Display();
}

void StatsDisplay::Display() const noexcept
{
	m_temperatureStats.Display();
	m_humidityStats.Display();
	m_pressureStats.Display();
}