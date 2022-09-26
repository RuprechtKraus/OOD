#pragma once
#include "Observers/Observable.h"
#include "WeatherInfo.h"

class WeatherData : public Observable<WeatherInfo>
{
public:
	void SetMeasurements(double temp, double humidity, double pressure);
	void MeasurementsChanged();
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;

protected:
	WeatherInfo GetChangedData() const override;

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
};