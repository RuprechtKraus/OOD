#include "StatsDisplay.h"
#include <iostream>

using namespace std::placeholders;

void StatsDisplay::AddDataSource(
	IWeatherStation<WeatherInfo>& wd,
	double displayPriority)
{
	auto connection = wd.DoOnWeatherDataChange(
		std::bind(&StatsDisplay::Update, this, _1, _2),
		displayPriority);
	m_sources.emplace(&wd, DataSource{ connection, wd.GetStationType() });
}

void StatsDisplay::Update(IWeatherStation<WeatherInfo>* sender, const WeatherInfo& data)
{
	m_sources.at(sender).statistics.Update(data);
	Display(sender, data.stationType);
}

void StatsDisplay::Display(IWeatherStation<WeatherInfo>* source, WeatherStationType stationType) const
{
	std::cout << "Station Type: " << WeatherStationTypeToString(stationType) << std::endl;
	m_sources.at(source).statistics.Display();
}