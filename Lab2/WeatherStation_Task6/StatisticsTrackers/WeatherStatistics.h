#pragma once
#include "CardinalDirectionStatistics.h"
#include "ValueStatistics.h"
#include "WeatherInfo.h"
#include <optional>

class WindStatistics
{
public:
	WindStatistics();
	void Update(const WindInfo& windInfo) noexcept;
	void Display() const;

private:
	ValueStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
};

class WeatherStatistics
{
public:
	WeatherStatistics(bool includeWindStats);
	void Update(const WeatherInfo& weatherInfo) noexcept;
	void Display() const;

private:
	static std::optional<WindStatistics> CreateWindStatsOrNull(bool create);

	bool m_includeWindStats;
	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
	std::optional<WindStatistics> m_windStats;
};