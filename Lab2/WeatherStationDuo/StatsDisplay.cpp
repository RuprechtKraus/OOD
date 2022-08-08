#include "StatsDisplay.h"
#include <format>

StatisticsData::StatisticsData(const std::string& name, std::ostream& output)
	: m_valueName(name)
	, m_output(output)
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
	m_output << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
	m_output << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
	m_output << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
	m_output << "----------------" << std::endl;
}

StatsDisplay::StatsDisplay(std::ostream& output)
	: m_output(output)
{
}

void StatsDisplay::Update(const std::string& source, const WeatherInfo& data)
{
	if (!DoesSourceExist(source))
	{
		AddSource(source);
	}
	UpdateSourceData(source, data);
	DisplaySourceData(source);
}

void StatsDisplay::AddSource(const std::string& source)
{
	m_sources[source] = {
		{ m_temperatureDataName, std::make_shared<StatisticsData>(m_temperatureDataName, m_output) },
		{ m_humidityDataName, std::make_shared<StatisticsData>(m_humidityDataName, m_output) },
		{ m_pressureDataName, std::make_shared<StatisticsData>(m_pressureDataName, m_output) }
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

void StatsDisplay::DisplaySourceData(const std::string& source) const noexcept
{
	m_output << "Source " << source << std::endl;
	for (const auto& [_, data] : m_sources.at(source))
	{
		data.get()->Display();
	}
}