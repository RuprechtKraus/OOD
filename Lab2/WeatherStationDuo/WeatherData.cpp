#include "WeatherData.h"

WeatherData::WeatherData(const std::string& name, WeatherStationLocation location)
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

ChangedData<WeatherInfo, WeatherEvents> WeatherData::GetChangedData(WeatherEvents eventsToDisplay) const noexcept
{
	WeatherInfo info;
	info.temperature = m_temperature.GetValue();
	info.humidity = m_humidity.GetValue();
	info.pressure = m_pressure.GetValue();
	info.windSpeed = m_windSpeed.GetValue();
	info.windDirection = m_windDirection.GetValue();
	info.sourceLocation = m_stationLocation;
	info.events = eventsToDisplay;
	return { info, CollectChangedWeatherParameters() };
}

WeatherEvents WeatherData::CollectChangedWeatherParameters() const noexcept
{
	WeatherEvents we = static_cast<WeatherEvents>(0);
	if (m_temperature.IsChanged())
	{
		we |= TEMPERATURE_CHANGED;
	}
	if (m_humidity.IsChanged())
	{
		we |= HUMIDITY_CHANGED;
	}
	if (m_pressure.IsChanged())
	{
		we |= PRESSURE_CHANGED;
	}
	if (m_windSpeed.IsChanged())
	{
		we |= WIND_SPEED_CHANGED;
	}
	if (m_windDirection.IsChanged())
	{
		we |= WIND_DIRECTION_CHANGED;
	}
	return we;
}
