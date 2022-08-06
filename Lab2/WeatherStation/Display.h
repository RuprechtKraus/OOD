#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <iostream>

class Display : public IObserver<WeatherInfo>
{
private:
	void Update(const WeatherInfo& data) const override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};