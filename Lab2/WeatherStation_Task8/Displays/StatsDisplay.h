#pragma once
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherData.h"
#include "WeatherInfo.h"
#include "boost/signals2.hpp"
#include <unordered_map>

namespace signals = boost::signals2;

class StatsDisplay
{
private:
	struct DataSource
	{
		signals::scoped_connection connection;
		WeatherStatistics statistics;
	};

public:
	void AddDataSource(IWeatherStation<WeatherInfo>& wd, double displayPriority = 0);

private:
	void Update(IWeatherStation<WeatherInfo>* sender, const WeatherInfo& data);
	void Display(IWeatherStation<WeatherInfo>* source, WeatherStationType stationType) const;

	std::unordered_map<IWeatherStation<WeatherInfo>*, DataSource> m_sources;
};