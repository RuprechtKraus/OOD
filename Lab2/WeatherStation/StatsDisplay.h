#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <climits>
#include <iostream>
#include <map>
#include <string>

class StatisticsData
{
public:
	StatisticsData(const std::string& name);

	void Update(double value) noexcept;
	void Display() const noexcept;

private:
	std::string m_valueName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	void Update(const WeatherInfo& data) const;
	void Display() const noexcept;

	const std::string m_temperatureDataName{ "Temperature" };
	const std::string m_humidityDataName{ "Humidity" };
	const std::string m_pressureDataName{ "Pressure" };

	std::map<std::string, std::shared_ptr<StatisticsData>> m_staticData{
		{ m_temperatureDataName, std::make_shared<StatisticsData>(m_temperatureDataName) },
		{ m_humidityDataName, std::make_shared<StatisticsData>(m_humidityDataName) },
		{ m_pressureDataName, std::make_shared<StatisticsData>(m_pressureDataName) }
	};
};