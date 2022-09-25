#include "Display.h"
#include "Utilities/CardinalDirectionUtils.h"
#include <iostream>

void Display::Update(const WeatherInfo& data)
{
	std::cout << "Current " << data.valueName << ' ';
	try
	{
		DisplayValue(data);
	}
	catch (const std::exception&)
	{
	}
	std::cout << "----------------" << std::endl;
}

void Display::DisplayValue(const WeatherInfo& data)
{
	if (data.event != WIND_DIRECTION_CHANGED)
	{
		double value = std::get<double>(data.value);
		std::cout << value << std::endl;
	}
	else
	{
		std::string direction = DegreesToCardinalDirection(std::get<WindInfo>(data.value).direction);
		std::cout << direction << std::endl;
	}
}