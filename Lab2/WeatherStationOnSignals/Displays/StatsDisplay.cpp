#include "StatsDisplay.h"
#include <ranges>

using namespace std::placeholders;

StatsDisplay::StatsDisplay(std::ostream& output)
	: m_output(output)
{
}

void StatsDisplay::AddDataSource(IWeatherStation& wd, WeatherEvent events, double priority)
{
	auto connection = wd.DoOnWeatherDataChange(bind([this](
		IWeatherStation* source,
		const std::vector<WeatherInfo>& info) {
		std::ranges::for_each(info, bind(&StatsDisplay::Update, this, source, _1));
	}, _1, _2),	priority);
	m_connections.emplace(&wd, SourceInfo{ connection, WeatherStatistics(m_output), events });
}

void StatsDisplay::RemoveDataSource(IWeatherStation& wd)
{
	m_connections.erase(&wd);
}

void StatsDisplay::SetEvents(IWeatherStation& wd, WeatherEvent events)
{
	m_connections.at(&wd).events = events;
}

void StatsDisplay::AddEvents(IWeatherStation& wd, WeatherEvent events)
{
	m_connections.at(&wd).events |= events;
}

void StatsDisplay::RemoveEvents(IWeatherStation& wd, WeatherEvent events)
{
	m_connections.at(&wd).events &= ~events;
}

void StatsDisplay::Update(IWeatherStation* source, const WeatherInfo& data)
{
	if (!m_connections.contains(source))
	{
		throw std::runtime_error("No such source");
	}

	if (!(m_connections[source].events & data.event))
	{
		return;
	}

	UpdateSourceData(source, data);
	DisplaySourceData(data.sourceName, source, data.event);
}

void StatsDisplay::UpdateSourceData(IWeatherStation* source, const WeatherInfo& newData)
{
	m_connections[source].statistics.AddEntry(newData);
}

void StatsDisplay::DisplaySourceData(
	const std::string& sourceName, 
	IWeatherStation* source, 
	WeatherEvent event) const noexcept
{
	m_output << "Source " << sourceName  << std::endl;
	m_connections.at(source).statistics.Display(event);
	m_output << "----------------" << std::endl;
}