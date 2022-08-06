#pragma once
#include "IObserver.h"
#include "Observable.h"

struct WeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class WeatherData : public Observable<WeatherInfo>
{
public:
	double GetTemperature() const noexcept;
	double GetHumidity() const noexcept;
	double GetPressure() const noexcept;
	void MeasurementsChanged() noexcept;
	void SetMeasurements(double temp, double humidity, double pressure) noexcept;

protected:
	WeatherInfo GetChangedData() const noexcept override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};
