#include "WeatherData.h"

WeatherData::WeatherData(const std::string& name)
	: Observable(name)
{
}

double WeatherData::GetTemperature() const noexcept
{
	return m_temperature;
}

double WeatherData::GetHumidity() const noexcept
{
	return m_humidity;
}

double WeatherData::GetPressure() const noexcept
{
	return m_pressure;
}

double WeatherData::GetWindSpeed() const noexcept
{
	return m_wind ? m_wind.value().speed : 0.0;
}

double WeatherData::GetWindDirection() const noexcept
{
	return m_wind ? m_wind.value().direction : std::numeric_limits<double>::quiet_NaN();
}

void WeatherData::MeasurementsChanged() noexcept
{
	NotifyObservers();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure) noexcept
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	MeasurementsChanged();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure, 
	double windSpeed, double windDirection) noexcept
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_wind.emplace(windSpeed, windDirection);
	MeasurementsChanged();
}

WeatherInfo WeatherData::GetChangedData() const noexcept
{
	WeatherInfo info;
	info.temperature = m_temperature;
	info.humidity = m_humidity;
	info.pressure = m_pressure;
	if (m_wind)
	{
		info.windInfo = m_wind;
	}
	return info;
}