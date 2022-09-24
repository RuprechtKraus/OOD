#include "WeatherStatistics.h"

WeatherStatistics::WeatherStatistics()
	: m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
{
}

void WeatherStatistics::Update(const WeatherInfo& weatherInfo) noexcept
{
	m_temperatureStats.Update(weatherInfo.temperature);
	m_humidityStats.Update(weatherInfo.humidity);
	m_pressureStats.Update(weatherInfo.pressure);
}

void WeatherStatistics::Display() const noexcept
{
	m_temperatureStats.Display();
	m_humidityStats.Display();
	m_pressureStats.Display();
}