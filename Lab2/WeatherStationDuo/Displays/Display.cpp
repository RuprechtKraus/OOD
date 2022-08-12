#include "Display.h"
#include "WeatherData.h"
#include <format>

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(const WeatherInfo& data)
{
	m_output << "Source " << data.sourceName << std::endl;
	m_output << std::format("Current {} ", data.valueName);
	try
	{
		DisplayValue(data);
	}
	catch (const std::bad_variant_access& e)
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