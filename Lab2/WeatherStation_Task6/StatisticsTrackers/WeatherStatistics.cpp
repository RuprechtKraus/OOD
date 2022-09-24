#include "WeatherStatistics.h"

WeatherStatistics::WeatherStatistics(WeatherStationType sourceType)
	: m_sourceType(sourceType)
	, m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
	, m_windSpeed("Wind Speed")
	, m_windDirection("Wind Direction")
{
}

void WeatherStatistics::Update(const WeatherInfo& weatherInfo) noexcept
{
	m_temperatureStats.Update(weatherInfo.temperature);
	m_humidityStats.Update(weatherInfo.humidity);
	m_pressureStats.Update(weatherInfo.pressure);

	if (m_sourceType == WeatherStationType::OUTSIDE)
	{
		m_windSpeed.Update(weatherInfo.windInfo.speed);
		m_windDirection.Update(weatherInfo.windInfo);
	}
}

void WeatherStatistics::Display() const noexcept
{
	m_temperatureStats.Display();
	m_humidityStats.Display();
	m_pressureStats.Display();

	if (m_sourceType == WeatherStationType::OUTSIDE)
	{
		m_windSpeed.Display();
		m_windDirection.Display();
	}
}