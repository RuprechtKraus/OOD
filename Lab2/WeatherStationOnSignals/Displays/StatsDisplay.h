#pragma once
#include "IWeatherDisplay.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherData.h"
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

	void AddDataSource(WeatherData& wd, WeatherEvent events, double priority = 0);
	void Update(const WeatherInfo& data) override;

private:
	void DisplaySourceData(const std::string& source, WeatherEvent event) const noexcept;
	void UpdateSourceData(const std::string& source, const WeatherInfo& newData);

	std::unordered_map<std::string, SourceInfo> m_connections;
	std::ostream& m_output;
};