#include "StatsDisplay.h"
#include <iostream>

void StatsDisplay::Update(WeatherInfo const& data)
{
	m_sources.try_emplace(data.stationType, data.stationType);
	m_sources.at(data.stationType).Update(data);
	Display(data.stationType);
}

void StatsDisplay::Display(WeatherStationType source) const noexcept
{
	std::cout << "Station Type: " << WeatherStationTypeToString(source) << std::endl;
	m_sources.at(source).Display();
}