#include "WeatherData.h"

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

WeatherInfo WeatherData::GetChangedData() const noexcept
{
	WeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	return info;
}