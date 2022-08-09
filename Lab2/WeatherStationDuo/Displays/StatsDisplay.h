#pragma once
#include "Observers/IObserver.h"
#include "WeatherData.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include <unordered_map>

class StatsDisplay : public IObserver<WeatherInfo>
{
public:
	StatsDisplay(std::ostream& output = std::cout);

private:
	void Update(const std::string& source, const WeatherInfo& data) override;
	void DisplaySourceData(const std::string& source) const noexcept;
	void UpdateSourceData(const std::string& source, const WeatherInfo& newData);
	bool DoesSourceExist(const std::string& source) const noexcept;

	std::unordered_map<std::string, WeatherStatistics> m_sources;
	std::ostream& m_output;
};