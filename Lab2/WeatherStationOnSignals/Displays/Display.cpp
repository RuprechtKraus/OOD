#include "Display.h"
#include "WeatherData.h"
#include <format>
#include <ranges>

using namespace std::placeholders;

Display::Display(WeatherData& wd, WeatherEvent events, double priority, std::ostream& output)
	: m_events(events)
	, m_output(output)
{
	m_connection = wd.DoOnWeatherDataChange(bind([this](const std::vector<WeatherInfo>& info) {
		std::ranges::for_each(info, bind(&Display::Update, this, _1));
	}, _1), priority);
}

void Display::Update(const WeatherInfo& data)
{
	if (!(m_events & data.event))
	{
		return;
	}

	m_output << "Source " << data.sourceName << std::endl;
	m_output << std::format("Current {} ", data.valueName);
	try
	{
		DisplayValue(data);
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