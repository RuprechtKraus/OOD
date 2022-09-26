#include "Display.h"
#include <iostream>

void Display::Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data)
{
	std::cout << "Station Type: ";

	if (&sender == &m_insideSource)
	{
		std::cout << "Inside" << std::endl;
	}
	else if (&sender == &m_outsideSource)
	{
		std::cout << "Outside" << std::endl;
	}

	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}