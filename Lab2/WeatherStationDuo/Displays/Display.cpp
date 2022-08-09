#include "Display.h"
#include "Helpers/CardinalDirectionHelper.h"
#include "WeatherData.h"

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(const std::string& source, const WeatherInfo& data) noexcept
{
	m_output << "Source " << source << std::endl;
	m_output << "Current Temp " << data.temperature << std::endl;
	m_output << "Current Hum " << data.humidity << std::endl;
	m_output << "Current Pressure " << data.pressure << std::endl;
	if (data.windInfo)
	{
		m_output << "Current Wind speed " << data.windInfo.value().speed << std::endl;
		m_output << "Current Wind direction " << DegreesToCardinalDirection(
			data.windInfo.value().direction) << std::endl;
	}
	m_output << "----------------" << std::endl;
}