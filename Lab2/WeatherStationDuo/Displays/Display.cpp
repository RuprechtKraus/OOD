#include "Display.h"
#include "Helpers/CardinalDirectionHelper.h"
#include "WeatherData.h"
#include <format>

Display::Display(std::ostream& output)
	: m_output(output)
{
}

void Display::Update(const WeatherInfo& data) noexcept
{
	m_output << "Source " << data.sourceName << std::endl;
	m_output << std::format("{} {}", data.valueName, data.value) << std::endl;
	m_output << "----------------" << std::endl;
}