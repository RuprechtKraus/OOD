#include "StatsDisplay.h"
#include <format>

StatisticsData::StatisticsData(const std::string& name)
	: m_valueName(name)
{
}

void StatisticsData::Update(double value) noexcept
{
	m_minValue = std::min(m_minValue, value);
	m_maxValue = std::max(m_maxValue, value);
	m_accValue += value;
	++m_countAcc;
}

void StatisticsData::Display() const noexcept
{
	std::cout << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
	std::cout << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
	std::cout << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
	std::cout << "----------------" << std::endl;
}

void StatsDisplay::Update(const std::string& source, const WeatherInfo& data)
{
	if (!DoesSourceExist(source))
	{
		AddSource(source);
	}
	UpdateSourceData(source, data);
	Display(source);
}

void StatsDisplay::AddSource(const std::string& source)
{
	m_sources[source] = {
		{ m_temperatureDataName, std::make_shared<StatisticsData>(m_temperatureDataName) },
		{ m_humidityDataName, std::make_shared<StatisticsData>(m_humidityDataName) },
		{ m_pressureDataName, std::make_shared<StatisticsData>(m_pressureDataName) }
	};
}

void StatsDisplay::UpdateSourceData(const std::string& source, const WeatherInfo& newData)
{
	m_sources.at(source)[m_temperatureDataName].get()->Update(newData.temperature);
	m_sources.at(source)[m_humidityDataName].get()->Update(newData.humidity);
	m_sources.at(source)[m_pressureDataName].get()->Update(newData.pressure);
}

bool StatsDisplay::DoesSourceExist(const std::string& source) const noexcept
{
	return m_sources.find(source) != m_sources.end() ? true : false;
}

void StatsDisplay::Display(const std::string& source) const noexcept
{
	std::cout << "Source " << source << std::endl;
	for (const auto& [_, data] : m_sources.at(source))
	{
		data.get()->Display();
	}
}