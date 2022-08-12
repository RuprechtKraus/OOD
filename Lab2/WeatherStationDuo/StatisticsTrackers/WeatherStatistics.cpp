#include "WeatherStatistics.h"
#include "WeatherEvent.h"

WeatherStatistics::WeatherStatistics(std::ostream& output)
	: m_output(output)
	, m_temperature(NumericStatistics("Temp", m_output))
	, m_humidity(NumericStatistics("Hum", m_output))
	, m_pressure(NumericStatistics("Pressure", m_output))
	, m_windSpeed(NumericStatistics("Wind speed", m_output))
	, m_windDirection(CardinalDirectionStatistics("Wind direction", m_output))
{
}

void WeatherStatistics::AddEntry(const WeatherInfo& weatherInfo)
{
	try
	{
		TryAddEntry(weatherInfo);
	}
	catch (const std::bad_variant_access& e)
	{
		throw std::runtime_error("Incorrect event value");
	}
	catch (const std::runtime_error& e)
	{
		throw;
	}
}

void WeatherStatistics::TryAddEntry(const WeatherInfo& weatherInfo)
{
	switch (weatherInfo.event)
	{
	case TEMPERATURE_CHANGED:
		m_temperature.AddEntry(std::get<double>(weatherInfo.value));
		break;
	case HUMIDITY_CHANGED:
		m_humidity.AddEntry(std::get<double>(weatherInfo.value));
		break;
	case PRESSURE_CHANGED:
		m_pressure.AddEntry(std::get<double>(weatherInfo.value));
		break;
	case WIND_SPEED_CHANGED:
		m_windSpeed.AddEntry(std::get<double>(weatherInfo.value));
		break;
	case WIND_DIRECTION_CHANGED:
		m_windDirection.AddEntry(std::get<WindInfo>(weatherInfo.value));
		break;
	default:
		throw std::runtime_error("Wrong weather event");
	}
}

void WeatherStatistics::Display(WeatherEvent event) const noexcept
{
	switch (event)
	{
	case TEMPERATURE_CHANGED:
		m_temperature.Display();
		break;
	case HUMIDITY_CHANGED:
		m_humidity.Display();
		break;
	case PRESSURE_CHANGED:
		m_pressure.Display();
		break;
	case WIND_SPEED_CHANGED:
		m_windSpeed.Display();
		break;
	case WIND_DIRECTION_CHANGED:
		m_windDirection.Display();
		break;
	default:
		break;
	}
}