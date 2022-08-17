#pragma once
#include "Helpers/CardinalDirectionHelper.h"
#include "WeatherData.h"
#include "WeatherEvent.h"
#include "IWeatherDisplay.h"
#include <iostream>

class Display : IWeatherDisplay
{
public:
	Display(WeatherData& wd, WeatherEvent events, double priority = 0, std::ostream& output = std::cout);

	void Update(const WeatherInfo& info) override;

private:
	void DisplayValue(const WeatherInfo& data) const;

	signals::scoped_connection m_connection;
	WeatherEvent m_events;
	std::ostream& m_output;
};
