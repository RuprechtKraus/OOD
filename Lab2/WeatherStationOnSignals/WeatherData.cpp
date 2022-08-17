#include "WeatherData.h"
#include <unordered_map>

WeatherData::WeatherData(const std::string& name, StationType location)
	: m_name(name)
	, m_stationLocation(location)
{
}

std::string WeatherData::GetName() const noexcept
{
	return m_name;
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
	m_signal(this, GetChangedData());
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
	if (m_stationLocation == StationType::INSIDE)
	{
		return SetMeasurements(temp, humidity, pressure);
	}

	m_humidity.UpdateValue(humidity);
	m_temperature.UpdateValue(temp);
	m_pressure.UpdateValue(pressure);
	m_windSpeed.UpdateValue(windSpeed);
	m_windDirection.UpdateValue(windDirection);
	MeasurementsChanged();
}

signals::connection WeatherData::DoOnWeatherDataChange(const slot_type& slot, double priority)
{
	return m_signal.connect(priority, slot);
}

WeatherData::Container WeatherData::GetChangedData() const noexcept
{
	return CollectChangedWeatherParameters();
}

WeatherData::Container WeatherData::CollectChangedWeatherParameters() const noexcept
{
	Container info;
	if (m_temperature.IsChanged())
	{
		info.push_back(CreateTemperatureInfo());
	}
	if (m_humidity.IsChanged())
	{
		info.push_back(CreateHumidityInfo());
	}
	if (m_pressure.IsChanged())
	{
		info.push_back(CreatePressureInfo());
	}
	if (m_stationLocation == StationType::INSIDE)
	{
		return info;
	}
	if (m_windSpeed.IsChanged())
	{
		info.push_back(CreateWindSpeedInfo());
	}
	if (m_windDirection.IsChanged())
	{
		info.push_back(CreateWindDirectionInfo());
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