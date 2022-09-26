#include "Display.h"
#include "Utilities/CardinalDirectionUtils.h"
#include <iostream>

void Display::Update(const IObservable<WeatherInfo>& sender, WeatherInfo const& data)
{
	std::cout << "Station Type: " << GetStationType(sender) << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;

	if (IsOutsideStation(sender))
	{
		std::cout << "Current Wind Speed " << data.windInfo.speed << std::endl;
		std::cout << "Current Wind Direction "
				  << DegreesToCardinalDirection(data.windInfo.direction) << std::endl;
	}

	std::cout << "----------------" << std::endl;
}

std::string Display::GetStationType(const IObservable<WeatherInfo>& observable) const
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

bool Display::IsInsideStation(const IObservable<WeatherInfo>& observable) const noexcept
{
	return &observable == &m_insideSource;
}

bool Display::IsOutsideStation(const IObservable<WeatherInfo>& observable) const noexcept
{
	return &observable == &m_outsideSource;
}