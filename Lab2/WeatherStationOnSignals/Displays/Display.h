#pragma once
#include "Helpers/CardinalDirectionHelper.h"
#include "IWeatherDisplay.h"
#include "WeatherData.h"
#include "WeatherEvent.h"
#include <iostream>
#include <unordered_map>

class Display : public IWeatherDisplay
{
	struct SourceInfo
	{
		signals::scoped_connection connection;
		WeatherEvent events;
	};

public:
	Display(std::ostream& output = std::cout);

	void AddDataSource(IWeatherStation& wd, WeatherEvent events, double priority = 0) override;
	void RemoveDataSource(IWeatherStation& wd) override;
	void Update(IWeatherStation* source, const WeatherInfo& info) override;

private:
	void DisplayValue(const WeatherInfo& data) const;

	std::unordered_map<IWeatherStation*, SourceInfo> m_connections;
	std::ostream& m_output;
};
