#include "WeatherData.h"

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

void WeatherData::MeasurementsChanged()
{
	NotifyObservers();
}

double WeatherData::GetTemperature() const
{
	return m_temperature;
}

double WeatherData::GetHumidity() const
{
	return m_humidity;
}

double WeatherData::GetPressure() const
{
	return m_pressure;
}

double WeatherData::GetWindSpeed() const
{
	return m_windSpeed;
}

double WeatherData::GetWindDirecion() const
{
	return m_windDirection;
}

WeatherInfo WeatherData::GetChangedData() const
{
	WeatherInfo info;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	info.windInfo.speed = GetWindSpeed();
	info.windInfo.direction = GetWindDirecion();
	return info;
}