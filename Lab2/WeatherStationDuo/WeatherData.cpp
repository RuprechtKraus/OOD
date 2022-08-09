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
	return m_windSpeed;
}

double WeatherData::GetWindDirection() const noexcept
{
	return m_windDirection;
}

void WeatherData::MeasurementsChanged() noexcept
{
	NotifyObservers();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure, 
	double windSpeed, double windDirection) noexcept
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windDirection = windDirection;
	MeasurementsChanged();
}

WeatherInfo WeatherData::GetChangedData() const noexcept
{
	WeatherInfo info;
	info.temperature = m_temperature;
	info.humidity = m_humidity;
	info.pressure = m_pressure;
	info.windInfo.speed = m_windSpeed;
	info.windInfo.direction = m_windDirection;
	return info;
}