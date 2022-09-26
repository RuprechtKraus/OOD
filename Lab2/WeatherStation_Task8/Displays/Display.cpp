#include "Display.h"
#include "Utilities/CardinalDirectionUtils.h"
#include <iostream>

using namespace std::placeholders;

void Display::AddDataSource(IWeatherStation<WeatherInfo>& wd, double displayPriority)
{
	auto connection = wd.DoOnWeatherDataChange(
		std::bind(&Display::Update, this, _1, _2),
		displayPriority);
	m_connections.push_back(std::move(connection));
}

void Display::Update(IWeatherStation<WeatherInfo>*, const WeatherInfo& data)
{
	std::cout << "Station Type: " << WeatherStationTypeToString(data.stationType) << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;

	if (data.stationType == WeatherStationType::OUTSIDE)
	{
		std::cout << "Current Wind Speed " << data.windInfo.speed << std::endl;
		std::cout << "Current Wind Direction "
				  << DegreesToCardinalDirection(data.windInfo.direction) << std::endl;
	}

	std::cout << "----------------" << std::endl;
}