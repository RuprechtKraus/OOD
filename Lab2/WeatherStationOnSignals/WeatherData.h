#pragma once
#include "Helpers/ValueTracker.h"
#include "WeatherInfo.h"
#include "WeatherStationLocation.h"
#include <boost/signals2.hpp>
#include <string>
#include <vector>

namespace signals = boost::signals2;

class IWeatherStation
{
public:
	using Container = std::vector<WeatherInfo>;

private:
	using Signature = void(const Container&);
	
protected:
	using signal_type = boost::signals2::signal<Signature,
		signals::optional_last_value<boost::function_traits<Signature>::result_type>,
		int,
		std::greater<int>>;

public:
	using slot_type = signal_type::slot_type;

	virtual signals::connection DoOnWeatherDataChange(const slot_type& slot, double priority) = 0;
	virtual Container GetChangedData() const = 0;
};

class WeatherData : IWeatherStation
{
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