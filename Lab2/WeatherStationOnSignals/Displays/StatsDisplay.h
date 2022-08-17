#pragma once
#include "IWeatherDisplay.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherData.h"
#include "WeatherEvent.h"
#include <unordered_map>

class StatsDisplay : public IWeatherDisplay
{
	struct SourceInfo
	{
		signals::scoped_connection connection;
		WeatherStatistics statistics;
		WeatherEvent events;
	};

public:
	StatsDisplay(std::ostream& output = std::cout);

	void AddDataSource(IWeatherStation& wd, WeatherEvent events, double priority = 0) override;
	void RemoveDataSource(IWeatherStation& wd) override;
	void Update(IWeatherStation* source, const WeatherInfo& data) override;

private:
	void DisplaySourceData(const std::string& sourceName, IWeatherStation* source, WeatherEvent event) const noexcept;
	void UpdateSourceData(IWeatherStation* source, const WeatherInfo& newData);

	std::unordered_map<IWeatherStation*, SourceInfo> m_connections;
	std::ostream& m_output;
};