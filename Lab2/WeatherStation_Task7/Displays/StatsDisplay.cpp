#include "StatsDisplay.h"
#include <stdexcept>

StatsDisplay::StatsDisplay()
	: m_temperatureStats("Temperature")
	, m_humidityStats("Humidity")
	, m_pressureStats("Pressure")
	, m_windSpeed("Wind Speed")
	, m_windDirection("Wind Direction")
{
}

void StatsDisplay::Update(const WeatherInfo& data)
{
	try
	{
		AddEntry(data);
		Display(data.event);
	}
	catch (const std::exception&)
	{
	}
}

void StatsDisplay::AddEntry(const WeatherInfo& data)
{
	switch (data.event)
	{
	case TEMPERATURE_CHANGED:
		m_temperatureStats.Update(std::get<double>(data.value));
		break;
	case HUMIDITY_CHANGED:
		m_humidityStats.Update(std::get<double>(data.value));
		break;
	case PRESSURE_CHANGED:
		m_pressureStats.Update(std::get<double>(data.value));
		break;
	case WIND_SPEED_CHANGED:
		m_windSpeed.Update(std::get<double>(data.value));
		break;
	case WIND_DIRECTION_CHANGED:
		m_windDirection.Update(std::get<WindInfo>(data.value));
		break;
	default:
		throw std::logic_error("Invalid weather event");
	}
}

void StatsDisplay::Display(WeatherEvent event) const
{
	switch (event)
	{
	case TEMPERATURE_CHANGED:
		m_temperatureStats.Display();
		break;
	case HUMIDITY_CHANGED:
		m_humidityStats.Display();
		break;
	case PRESSURE_CHANGED:
		m_pressureStats.Display();
		break;
	case WIND_SPEED_CHANGED:
		m_windSpeed.Display();
		break;
	case WIND_DIRECTION_CHANGED:
		m_windDirection.Display();
		break;
	default:
		throw std::logic_error("Invalid weather event");
	}
}