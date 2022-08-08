#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <climits>
#include <iostream>
#include <unordered_map>
#include <string>

class IStatisticsData
{
public:
	virtual void Update(double value) = 0;
	virtual void Display() const = 0;
};

class StatisticsData : IStatisticsData
{
public:
	StatisticsData(const std::string& name, std::ostream& output = std::cout);

	void Update(double value) noexcept override;
	void Display() const noexcept override;

private:
	std::ostream& m_output;
	std::string m_valueName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class StatsDisplay : public IObserver<WeatherInfo>
{
public:
	StatsDisplay(std::ostream& output = std::cout);

private:
	using SourceData = std::unordered_map<std::string, std::shared_ptr<StatisticsData>>;

	void AddSource(const std::string& source);
	void Update(const std::string& source, const WeatherInfo& data) override;
	void DisplaySourceData(const std::string& source) const noexcept;
	void UpdateSourceData(const std::string& source, const WeatherInfo& newData);
	bool DoesSourceExist(const std::string& source) const noexcept;

	const std::string m_temperatureDataName{ "Temp" };
	const std::string m_humidityDataName{ "Hum" };
	const std::string m_pressureDataName{ "Pressure" };

	std::unordered_map<std::string, SourceData> m_sources;
	std::ostream& m_output;
};