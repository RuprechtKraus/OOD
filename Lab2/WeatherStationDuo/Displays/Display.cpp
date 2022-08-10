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
	DisplayValue("Temp", data.temperature, data.events, TEMPERATURE_CHANGED);
	DisplayValue("Hum", data.humidity, data.events, HUMIDITY_CHANGED);
	DisplayValue("Pressure", data.pressure, data.events, PRESSURE_CHANGED);
	if (data.sourceLocation == WeatherStationLocation::OUTSIDE)
	{
		DisplayValue("Wind speed", data.windSpeed, data.events, WIND_SPEED_CHANGED);
		DisplayValue("Wind direction", DegreesToCardinalDirection(data.windDirection), data.events, WIND_DIRECTION_CHANGED);
	}
	m_output << "----------------" << std::endl;
}

template<typename T>
void Display::DisplayValue(const std::string& valueName, const T value,
	WeatherEvents happendEvents, WeatherEvents requiredEvent)
{
	if (happendEvents & requiredEvent)
	{
		m_output << std::format("Current {} {}", valueName, value) << std::endl;
	}
}