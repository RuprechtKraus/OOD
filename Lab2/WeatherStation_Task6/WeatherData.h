#pragma once
#include "Observers/Observable.h"
#include "WeatherInfo.h"

class WeatherData : public Observable<WeatherInfo>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure);
	void MeasurementsChanged();
	double GetTemperature() const noexcept;
	double GetHumidity() const noexcept;
	double GetPressure() const noexcept;

protected:
	WeatherInfo GetChangedData() const override;

	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};

using InsideWeatherData = WeatherData;

class OutsideWeatherData : public WeatherData
{
public:
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