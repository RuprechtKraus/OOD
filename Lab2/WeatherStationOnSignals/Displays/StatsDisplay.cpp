#include "StatsDisplay.h"
#include <ranges>

using namespace std::placeholders;

StatsDisplay::StatsDisplay(std::ostream& output)
	: m_output(output)
{
}

void StatsDisplay::AddDataSource(WeatherData& wd, WeatherEvent events, double priority)
{
	auto connection = wd.DoOnWeatherDataChange(bind([this](const std::vector<WeatherInfo>& info) {
		std::ranges::for_each(info, bind(&StatsDisplay::Update, this, _1));
	}, _1),	priority);
	m_connections.emplace(wd.GetName(), SourceInfo{ connection, WeatherStatistics(m_output), events });
}

void StatsDisplay::Update(const WeatherInfo& data)
{
	if (!m_connections.contains(data.sourceName))
	{
		throw std::runtime_error("No such source");
	}

	if (!(m_connections[data.sourceName].events & data.event))
	{
		return;
	}

	UpdateSourceData(data.sourceName, data);
	DisplaySourceData(data.sourceName, data.event);
}

void StatsDisplay::UpdateSourceData(const std::string& source, const WeatherInfo& newData)
{
	m_connections[source].statistics.AddEntry(newData);
}

void StatsDisplay::DisplaySourceData(const std::string& source, WeatherEvent event) const noexcept
{
	m_output << "Source " << source << std::endl;
	m_connections.at(source).statistics.Display(event);
	m_output << "----------------" << std::endl;
}