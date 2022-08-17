#pragma once
#include "Helpers/ValueTracker.h"
#include "IWeatherStation.h"
#include "WeatherStationLocation.h"
#include <boost/signals2.hpp>
#include <string>
#include <vector>

class WeatherData : public IWeatherStation
{
public:
	WeatherData(const std::string& name, StationType location);

	std::string GetName() const noexcept;
	double GetTemperature() const noexcept;
	double GetHumidity() const noexcept;
	double GetPressure() const noexcept;
	double GetWindSpeed() const noexcept;
	double GetWindDirection() const noexcept;
	void MeasurementsChanged() noexcept;
	void SetMeasurements(double temp, double humidity, double pressure) noexcept;
	void SetMeasurements(double temp, double humidity, double pressure,
		double windSpeed, double windDirection) noexcept;
	signals::connection DoOnWeatherDataChange(const slot_type& slot, double priority) override;

protected:
	Container GetChangedData() const noexcept override;

private:
	Container CollectChangedWeatherParameters() const noexcept;
	WeatherInfo CreateTemperatureInfo() const noexcept;
	WeatherInfo CreateHumidityInfo() const noexcept;
	WeatherInfo CreatePressureInfo() const noexcept;
	WeatherInfo CreateWindSpeedInfo() const noexcept;
	WeatherInfo CreateWindDirectionInfo() const noexcept;

	signal_type m_signal;
	std::string m_name;
	StationType m_stationLocation;
	ValueTracker<double> m_temperature;
	ValueTracker<double> m_humidity;
	ValueTracker<double> m_pressure;
	ValueTracker<double> m_windSpeed;
	ValueTracker<double> m_windDirection;
};