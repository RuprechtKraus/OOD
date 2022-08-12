#pragma once
#include "Helpers/ValueTracker.h"
#include "Observers/PriorityObservable.h"
#include "WeatherInfo.h"
#include "WeatherStationLocation.h"

class WeatherData : public PriorityObservable<WeatherInfo, WeatherEvent>
{
	using Base = PriorityObservable<WeatherInfo, WeatherEvent>;
	using EventData = Base::EventData;

public:
	WeatherData(const std::string& name, StationType location);

	double GetTemperature() const noexcept;
	double GetHumidity() const noexcept;
	double GetPressure() const noexcept;
	double GetWindSpeed() const noexcept;
	double GetWindDirection() const noexcept;
	void MeasurementsChanged() noexcept;
	void SetMeasurements(double temp, double humidity, double pressure) noexcept;
	void SetMeasurements(double temp, double humidity, double pressure,
		double windSpeed, double windDirection) noexcept;

protected:
	EventData GetChangedData() const noexcept override;

private:
	EventData CollectChangedWeatherParameters() const noexcept;
	WeatherInfo CreateTemperatureInfo() const noexcept;
	WeatherInfo CreateHumidityInfo() const noexcept;
	WeatherInfo CreatePressureInfo() const noexcept;
	WeatherInfo CreateWindSpeedInfo() const noexcept;
	WeatherInfo CreateWindDirectionInfo() const noexcept;

	StationType m_stationLocation;
	ValueTracker<double> m_temperature;
	ValueTracker<double> m_humidity;
	ValueTracker<double> m_pressure;
	ValueTracker<double> m_windSpeed;
	ValueTracker<double> m_windDirection;
};