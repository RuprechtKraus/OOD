#pragma once
#include "WeatherData.h"
#include "WeatherInfo.h"
#include "boost/signals2.hpp"
#include <vector>

namespace signals = boost::signals2;

class Display
{
public:
	void AddDataSource(IWeatherStation<WeatherInfo>& wd, double displayPriority = 0);

private:
	void Update(IWeatherStation<WeatherInfo>*, const WeatherInfo& data);

	std::vector<signals::scoped_connection> m_connections;
};
