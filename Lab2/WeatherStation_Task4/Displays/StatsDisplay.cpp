#include "StatsDisplay.h"
#include <iostream>

StatsDisplay::StatsDisplay(
	const IObservable<WeatherInfo>& insideSource, 
	const IObservable<WeatherInfo>& outsideSource)
	: m_insideDataSource(insideSource)
	, m_outsideDataSource(outsideSource)
{
}

void StatsDisplay::Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data)
{
	if (&sender == &m_insideDataSource.source)
	{
		m_insideDataSource.stats.Update(data);
		std::cout << "Station Type: Inside" << std::endl;
		m_insideDataSource.stats.Display();
	}
	else if (&sender == &m_outsideDataSource.source)
	{
		m_outsideDataSource.stats.Update(data);
		std::cout << "Station Type: Outside" << std::endl;
		m_outsideDataSource.stats.Display();
	}
}