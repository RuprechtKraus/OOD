#pragma once
#include "IWeatherDisplay.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherData.h"
#include <unordered_map>

class StatsDisplay : public IWeatherDisplay
{
public:
	StatsDisplay(WeatherData& wd, WeatherEvent events, double priority = 0, std::ostream& output = std::cout);

	void Update(const WeatherInfo& data) override;

private:
	void DisplaySourceData(const std::string& source, WeatherEvent event) const noexcept;
	void UpdateSourceData(const std::string& source, const WeatherInfo& newData);
	void CreateSourceIfNotExists(const std::string& source);

	std::unordered_map<std::string, WeatherStatistics> m_sources;
	signals::scoped_connection m_connection;
	WeatherEvent m_events;
	std::ostream& m_output;
};