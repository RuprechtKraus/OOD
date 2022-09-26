#pragma once
#include "IWeatherStation.h"
#include "WeatherInfo.h"

class WeatherData : public IWeatherStation<WeatherInfo>
{
public:
	WeatherData();

	signals::connection DoOnWeatherDataChange(const slot_type& slot, double priority) override;
	void SetMeasurements(double temp, double humidity, double pressure) noexcept;
	void MeasurementsChanged();
	double GetTemperature() const noexcept;
	double GetHumidity() const noexcept;
	double GetPressure() const noexcept;
	WeatherStationType GetStationType() const noexcept override;

protected:
	WeatherData(WeatherStationType stationType);

	WeatherInfo GetChangedData() const override;

	signal_type m_signal;
	WeatherStationType m_stationType;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

using InsideWeatherData = WeatherData;

class OutsideWeatherData : public WeatherData
{
public:
	OutsideWeatherData();

	void SetMeasurements(double temp, double humidity, double pressure,
		double windSpeed, double windDirection) noexcept;
	double GetWindSpeed() const noexcept;
	double GetWindDirection() const noexcept;

protected:
	WeatherInfo GetChangedData() const override;

private:
	double m_windSpeed = 0.0;
	double m_windDirection = NaN;
};