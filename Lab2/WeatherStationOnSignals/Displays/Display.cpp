#include "Display.h"
#include "WeatherData.h"
#include <format>
#include <ranges>

using namespace std::placeholders;

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::AddDataSource(IWeatherStation& wd, WeatherEvent events, double priority)
{
	auto connection = wd.DoOnWeatherDataChange(bind([this](
		IWeatherStation* source, 
		const std::vector<WeatherInfo>& info) {
		std::ranges::for_each(info, bind(&Display::Update, this, source, _1));
	}, _1, _2), priority);
	m_connections[&wd] = { connection, events };
}

void Display::RemoveDataSource(IWeatherStation& wd)
{
	m_connections.erase(&wd);
}

void Display::Update(IWeatherStation* source, const WeatherInfo& info)
{
	if (!m_connections.contains(source))
	{
		throw std::runtime_error("No such source");
	}

	if (!(m_connections[source].events & info.event))
	{
		return;
	}

	m_output << "Source " << info.sourceName << std::endl;
	m_output << std::format("Current {} ", info.valueName);
	try
	{
		DisplayValue(info);
	}
	catch (const std::bad_variant_access&)
	{
		m_output << "Incorrect value" << std::endl;
	}
	m_output << "----------------" << std::endl;
}

void Display::DisplayValue(const WeatherInfo& data) const
{
	if (data.event != WIND_DIRECTION_CHANGED)
	{
		double value = std::get<double>(data.value);
		m_output << value << std::endl;
	}
	else
	{
		std::string direction = DegreesToCardinalDirection(std::get<WindInfo>(data.value).direction);
		m_output << direction << std::endl;
	}
}