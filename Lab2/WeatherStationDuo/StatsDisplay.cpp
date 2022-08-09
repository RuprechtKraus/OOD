#include "StatsDisplay.h"

StatsDisplay::StatsDisplay(std::ostream& output)
	: m_output(output)
{
}

void StatsDisplay::Update(const std::string& source, const WeatherInfo& data)
{
	UpdateSourceData(source, data);
	DisplaySourceData(source);
}

void StatsDisplay::UpdateSourceData(const std::string& source, const WeatherInfo& newData)
{
	m_sources[source].AddData(newData);
}

bool StatsDisplay::DoesSourceExist(const std::string& source) const noexcept
{
	return m_sources.find(source) != m_sources.end() ? true : false;
}

void StatsDisplay::DisplaySourceData(const std::string& source) const noexcept
{
	m_output << "Source " << source << '\n'
			 << std::endl;
	m_sources.at(source).Display();
	m_output << "----------------" << std::endl;
}