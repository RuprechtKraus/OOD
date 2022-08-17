#pragma once
#include "Helpers/CardinalDirectionHelper.h"
#include "IWeatherDisplay.h"
#include "WeatherData.h"
#include "WeatherEvent.h"
#include <iostream>
#include <unordered_map>

class Display : IWeatherDisplay
{
	struct SourceInfo
	{
		signals::scoped_connection connection;
		WeatherEvent events;
	};

public:
	Display(std::ostream& output = std::cout);

	void AddDataSource(WeatherData& wd, WeatherEvent events, double priority = 0);
	void Update(const WeatherInfo& info) override;

private:
	void DisplayValue(const WeatherInfo& data) const;

	std::unordered_map<std::string, SourceInfo> m_connections;
	std::ostream& m_output;
};
