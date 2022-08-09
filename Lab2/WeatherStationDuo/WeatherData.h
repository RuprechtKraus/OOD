#pragma once
#include "IObserver.h"
#include "Observable.h"
#include "WeatherInfo.h"

class WeatherData : public Observable<WeatherInfo>
{
public:
	WeatherData(const std::string& name);

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
	WeatherInfo GetChangedData() const noexcept override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::optional<WindInfo> m_wind;
};