#include "WeatherData.h"
#include <unordered_map>

WeatherData::WeatherData(const std::string& name, StationType location)
	: PriorityObservable(name)
	, m_stationLocation(location)
{
}

double WeatherData::GetTemperature() const noexcept
{
	return m_temperature.GetValue();
}

double WeatherData::GetHumidity() const noexcept
{
	return m_humidity.GetValue();
}

double WeatherData::GetPressure() const noexcept
{
	return m_pressure.GetValue();
}

double WeatherData::GetWindSpeed() const noexcept
{
	return m_windSpeed.GetValue();
}

double WeatherData::GetWindDirection() const noexcept
{
	return m_windDirection.GetValue();
}

void WeatherData::MeasurementsChanged() noexcept
{
	NotifyObservers();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure) noexcept
{
	m_humidity.UpdateValue(humidity);
	m_temperature.UpdateValue(temp);
	m_pressure.UpdateValue(pressure);
	MeasurementsChanged();
}

void WeatherData::SetMeasurements(double temp, double humidity, double pressure,
	double windSpeed, double windDirection) noexcept
{
	m_humidity.UpdateValue(humidity);
	m_temperature.UpdateValue(temp);
	m_pressure.UpdateValue(pressure);
	m_windSpeed.UpdateValue(windSpeed);
	m_windDirection.UpdateValue(windDirection);
	MeasurementsChanged();
}

WeatherData::EventData WeatherData::GetChangedData() const noexcept
{
	return CollectChangedWeatherParameters();
}

WeatherData::EventData WeatherData::CollectChangedWeatherParameters() const noexcept
{
	std::unordered_map<WeatherEvent, WeatherInfo> info;
	if (m_temperature.IsChanged())
	{
		info.emplace(TEMPERATURE_CHANGED, CreateTemperatureInfo());
	}
	if (m_humidity.IsChanged())
	{
		info.emplace(HUMIDITY_CHANGED, CreateHumidityInfo());
	}
	if (m_pressure.IsChanged())
	{
		info.emplace(PRESSURE_CHANGED, CreatePressureInfo());
	}
	if (m_windSpeed.IsChanged())
	{
		info.emplace(WIND_SPEED_CHANGED, CreateWindSpeedInfo());
	}
	if (m_windDirection.IsChanged())
	{
		info.emplace(WIND_DIRECTION_CHANGED, CreateWindDirectionInfo());
	}
	return info;
}

WeatherInfo WeatherData::CreateTemperatureInfo() const noexcept
{
	return {
		m_temperature,
		"Temp",
		m_name,
		m_stationLocation,
		TEMPERATURE_CHANGED
	};
}

WeatherInfo WeatherData::CreateHumidityInfo() const noexcept
{
	return {
		m_humidity,
		"Hum",
		m_name,
		m_stationLocation,
		HUMIDITY_CHANGED
	};
}

WeatherInfo WeatherData::CreatePressureInfo() const noexcept
{
	return {
		m_pressure,
		"Pressure",
		m_name,
		m_stationLocation,
		PRESSURE_CHANGED
	};
}

WeatherInfo WeatherData::CreateWindSpeedInfo() const noexcept
{
	return {
		m_windSpeed,
		"Wind speed",
		m_name,
		m_stationLocation,
		WIND_SPEED_CHANGED
	};
}

WeatherInfo WeatherData::CreateWindDirectionInfo() const noexcept
{
	return {
		WindInfo{ m_windSpeed, m_windDirection },
		"Wind direction",
		m_name,
		m_stationLocation,
		WIND_DIRECTION_CHANGED
	};
}