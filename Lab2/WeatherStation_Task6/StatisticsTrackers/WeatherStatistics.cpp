#include "WeatherStatistics.h"

WeatherStatistics::WeatherStatistics(bool includeWindStats)
	: m_includeWindStats(includeWindStats)
	, m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
	, m_windStats(CreateWindStatsOrNull(includeWindStats))
{
}

void WeatherStatistics::Update(const WeatherInfo& weatherInfo) noexcept
{
	m_temperatureStats.Update(weatherInfo.temperature);
	m_humidityStats.Update(weatherInfo.humidity);
	m_pressureStats.Update(weatherInfo.pressure);

	if (m_windStats)
	{
		m_windStats.value().Update(weatherInfo.windInfo);
	}
}

void WeatherStatistics::Display() const
{
	m_temperatureStats.Display();
	m_humidityStats.Display();
	m_pressureStats.Display();

	if (m_windStats)
	{
		m_windStats.value().Display();
	}
}

std::optional<WindStatistics> WeatherStatistics::CreateWindStatsOrNull(bool create)
{
	return create ? std::make_optional<WindStatistics>() : std::nullopt;
}

WindStatistics::WindStatistics()
	: m_windSpeed("Wind Speed")
	, m_windDirection("Wind Direction")
{
}

void WindStatistics::Update(const WindInfo& windInfo) noexcept
{
	m_windSpeed.Update(windInfo.speed);
	m_windDirection.Update(windInfo);
}

void WindStatistics::Display() const
{
	m_windSpeed.Display();
	m_windDirection.Display();
}