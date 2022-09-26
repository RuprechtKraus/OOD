#include "StatsDisplay.h"
#include <iostream>

StatsDisplay::StatsDisplay(
	const IObservable<WeatherInfo>& insideSource,
	const IObservable<WeatherInfo>& outsideSource)
	: m_insideDataSource(insideSource, false)
	, m_outsideDataSource(outsideSource, true)
{
}

void StatsDisplay::Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data)
{
	if (IsInsideStation(sender))
	{
		m_insideDataSource.stats.Update(data);
		std::cout << "Station Type: " << GetStationType(sender) << std::endl;
		m_insideDataSource.stats.Display();
	}
	else if (IsOutsideStation(sender))
	{
		m_outsideDataSource.stats.Update(data);
		std::cout << "Station Type: " << GetStationType(sender) << std::endl;
		m_outsideDataSource.stats.Display();
	}
}

std::string StatsDisplay::GetStationType(const IObservable<WeatherInfo>& observable) const
{
	if (IsInsideStation(observable))
	{
		return "Inside";
	}
	else if (IsOutsideStation(observable))
	{
		return "Outside";
	}
}

bool StatsDisplay::IsInsideStation(const IObservable<WeatherInfo>& observable) const noexcept
{
	return &observable == &m_insideDataSource.source;
}

bool StatsDisplay::IsOutsideStation(const IObservable<WeatherInfo>& observable) const noexcept
{
	return &observable == &m_outsideDataSource.source;
}

StatsDisplay::DataSourceStats::DataSourceStats(
	const IObservable<WeatherInfo>& wd, 
	bool includeWindStats)
	: source(wd)
	, stats(includeWindStats)
{
}