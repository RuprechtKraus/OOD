#include "StatsDisplay.h"
#include <iostream>

void StatsDisplay::Update(const WeatherInfo& data)
{
	m_sources[data.stationType].Update(data);
	Display(data.stationType);
}

void StatsDisplay::Display(WeatherStationType source) const
{
	std::cout << "Station Type: " << WeatherStationTypeToString(source) << std::endl;
	m_sources.at(source).Display();
}