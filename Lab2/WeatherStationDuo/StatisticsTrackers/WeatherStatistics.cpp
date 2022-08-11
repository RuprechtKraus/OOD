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

void WeatherStatistics::AddEntry(const WeatherInfo& weatherInfo) noexcept
{
	/*AddValueEntry(m_temperature, weatherInfo.temperature, m_events, TEMPERATURE_CHANGED);
	AddValueEntry(m_humidity, weatherInfo.humidity, m_events, HUMIDITY_CHANGED);
	AddValueEntry(m_pressure, weatherInfo.pressure, m_events, PRESSURE_CHANGED);
	if (weatherInfo.sourceLocation == WeatherStationLocation::OUTSIDE)
	{
		AddValueEntry(m_windSpeed, weatherInfo.windSpeed, m_events, WIND_SPEED_CHANGED);
		AddValueEntry(m_windDirection, WindInfo{ weatherInfo.windSpeed, weatherInfo.windDirection },
			m_events, WIND_DIRECTION_CHANGED);
	}*/
}

void WeatherStatistics::Display() const noexcept
{
	/*DisplayValue(m_temperature, m_events, TEMPERATURE_CHANGED);
	DisplayValue(m_humidity, m_events, HUMIDITY_CHANGED);
	DisplayValue(m_pressure, m_events, PRESSURE_CHANGED);
	DisplayValue(m_windSpeed, m_events, WIND_SPEED_CHANGED);
	DisplayValue(m_windDirection, m_events, WIND_DIRECTION_CHANGED);*/
}

void WeatherStatistics::UpdateEvents(WeatherEvent newEvents) noexcept
{
	m_events = newEvents;
}

template <typename S, typename T>
void WeatherStatistics::AddValueEntry(S& statistics, const T& value,
	WeatherEvent events, WeatherEvent targetEvent)
{
	if (events & targetEvent)
	{
		statistics.AddEntry(value);
	}
}

template <typename S>
void WeatherStatistics::DisplayValue(S& statistics, WeatherEvent events, WeatherEvent targetEvent)
{
	if (events & targetEvent)
	{
		statistics.Display();
	}
}