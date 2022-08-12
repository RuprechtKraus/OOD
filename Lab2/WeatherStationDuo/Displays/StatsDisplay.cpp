#include "StatsDisplay.h"

StatsDisplay::StatsDisplay(std::ostream& output)
	: m_output(output)
{
}

void StatsDisplay::Update(const WeatherInfo& data)
{
	try
	{
		UpdateSourceData(data.sourceName, data);
		DisplaySourceData(data.sourceName, data.event);
	}
	catch (const std::runtime_error& e)
	{
		throw;
	}
}

void StatsDisplay::UpdateSourceData(const std::string& source, const WeatherInfo& newData)
{
	CreateSourceIfNotExists(source);
	try
	{
		m_sources[source].AddEntry(newData);
	}
	catch (const std::runtime_error& e)
	{
		m_sources.erase(source);
		throw;
	}
}

void StatsDisplay::CreateSourceIfNotExists(const std::string& source)
{
	if (!m_sources.contains(source))
	{
		m_sources.emplace(std::pair(source, WeatherStatistics(m_output)));
	}
}

void StatsDisplay::DisplaySourceData(const std::string& source, WeatherEvent event) const noexcept
{
	m_output << "Source " << source << std::endl;
	m_sources.at(source).Display(event);
	m_output << "----------------" << std::endl;
}