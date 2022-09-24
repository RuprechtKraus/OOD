#include "Display.h"
#include "Utilities/CardinalDirectionUtils.h"
#include <iostream>

void Display::Update(WeatherInfo const& data)
{
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