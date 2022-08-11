//#pragma once
//#include "Observers/IObserver.h"
//#include "StatisticsTrackers/WeatherStatistics.h"
//#include "WeatherData.h"
//#include <unordered_map>
//
//class StatsDisplay : public IObserver<WeatherInfo>
//{
//public:
//	StatsDisplay(std::ostream& output = std::cout);
//
//private:
//	void Update(const std::string& source, const WeatherInfo& data) override;
//	void DisplaySourceData(const std::string& source) const noexcept;
//	void UpdateSourceData(const std::string& source, const WeatherInfo& newData);
//	void CreateSourceIfNotExists(const std::string& source);
//
//	std::unordered_map<std::string, WeatherStatistics> m_sources;
//	std::ostream& m_output;
//};