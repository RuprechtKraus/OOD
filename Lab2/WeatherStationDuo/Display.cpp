#include "Display.h"
#include <iostream>

void Display::Update(const std::string& source, const WeatherInfo& data) noexcept
{
	std::cout << "Source " << source << std::endl;
	std::cout << "Current Temp " << data.temperature << std::endl;
	std::cout << "Current Hum " << data.humidity << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}