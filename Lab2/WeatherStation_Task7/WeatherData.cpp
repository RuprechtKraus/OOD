#include "WeatherData.h"

void WeatherData::SetMeasurements(double temp, double humidity, double pressure,
	double windSpeed, double windDirection) noexcept
{
	m_temperature.UpdateValue(temp);
	m_humidity.UpdateValue(humidity);
	m_pressure.UpdateValue(pressure);
	m_windSpeed.UpdateValue(windSpeed);
	m_windDirection.UpdateValue(windDirection);
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

WeatherData::EventsData WeatherData::GetChangedData() const
{
	return CollectChangedWeatherData();
}

WeatherData::EventsData WeatherData::CollectChangedWeatherData() const noexcept
{
	EventsData data;

	if (m_temperature.IsChanged())
	{
		data.emplace(TEMPERATURE_CHANGED, CreateTemperatureInfo());
	}

	if (m_humidity.IsChanged())
	{
		data.emplace(HUMIDITY_CHANGED, CreateHumidityInfo());
	}

	if (m_pressure.IsChanged())
	{
		data.emplace(PRESSURE_CHANGED, CreatePressureInfo());
	}

	if (m_windSpeed.IsChanged())
	{
		data.emplace(WIND_SPEED_CHANGED, CreateWindSpeedInfo());
	}

	if (m_windDirection.IsChanged())
	{
		data.emplace(WIND_DIRECTION_CHANGED, CreateWindDirectionInfo());
	}

	return data;
}

WeatherInfo WeatherData::CreateTemperatureInfo() const noexcept
{
	return {
		TEMPERATURE_CHANGED,
		"Temperature",
		m_temperature
	};
}

WeatherInfo WeatherData::CreateHumidityInfo() const noexcept
{
	return {
		HUMIDITY_CHANGED,
		"Humidity",
		m_humidity
	};
}

WeatherInfo WeatherData::CreatePressureInfo() const noexcept
{
	return {
		PRESSURE_CHANGED,
		"Pressure",
		m_pressure
	};
}

WeatherInfo WeatherData::CreateWindSpeedInfo() const noexcept
{
	return {
		WIND_SPEED_CHANGED,
		"Wind Speed",
		m_windSpeed
	};
}

WeatherInfo WeatherData::CreateWindDirectionInfo() const noexcept
{
	return {
		WIND_DIRECTION_CHANGED,
		"Wind Direction",
		WindInfo{ m_windDirection, m_windDirection }
	};
}