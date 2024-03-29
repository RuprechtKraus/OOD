#include "WeatherData.h"

WeatherData::WeatherData()
	: m_stationType(WeatherStationType::INSIDE)
{
}

WeatherData::WeatherData(WeatherStationType stationType)
	: m_stationType(stationType)
{
}

signals::connection WeatherData::DoOnWeatherDataChange(const slot_type& slot, double priority)
{
	return m_signal.connect(priority, slot);
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure) noexcept
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	MeasurementsChanged();
}

void WeatherData::MeasurementsChanged()
{
	m_signal(this, GetChangedData());
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

WeatherStationType WeatherData::GetStationType() const noexcept
{
	return m_stationType;
}

WeatherInfo WeatherData::GetChangedData() const
{
	WeatherInfo info;
	info.stationType = m_stationType;
	info.temperature = GetTemperature();
	info.humidity = GetHumidity();
	info.pressure = GetPressure();
	return info;
}

OutsideWeatherData::OutsideWeatherData()
	: WeatherData(WeatherStationType::OUTSIDE)
{
}

void OutsideWeatherData::SetMeasurements(double temp, double humidity, double pressure,
	double windSpeed, double windDirection) noexcept
{
	m_humidity = humidity;
	m_temperature = temp;
	m_pressure = pressure;
	m_windSpeed = windSpeed;
	m_windDirection = windDirection;
	MeasurementsChanged();
}

double OutsideWeatherData::GetWindSpeed() const noexcept
{
	return m_windSpeed;
}

double OutsideWeatherData::GetWindDirection() const noexcept
{
	return m_windDirection;
}

WeatherInfo OutsideWeatherData::GetChangedData() const
{
	WeatherInfo info = WeatherData::GetChangedData();
	info.windInfo.speed = m_windSpeed;
	info.windInfo.direction = m_windDirection;
	return info;
}