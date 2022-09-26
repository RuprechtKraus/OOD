#include "Display.h"
#include <iostream>

void Display::Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data)
{
	std::cout << "Station Type: " << GetStationType(sender) << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}

std::string Display::GetStationType(const IObservable<WeatherInfo>& sender) const
{
	if (&sender == &m_insideSource)
	{
		return "Inside";
	}
	else if (&sender == &m_outsideSource)
	{
		return "Outside";
	}
}