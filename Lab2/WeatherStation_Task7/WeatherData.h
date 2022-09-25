#pragma once
#include "Observers/Observable.h"
#include "Utilities/ValueTracker.h"
#include "WeatherEvent.h"
#include "WeatherInfo.h"

class WeatherData : public Observable<WeatherInfo, WeatherEvent>
{
private:
	using Base = Observable<WeatherInfo, WeatherEvent>;
	using EventsData = Base::EventsData;

public:
	void SetMeasurements(double temp, double humidity, double pressure,
		double windSpeed, double windDirection) noexcept;
	void MeasurementsChanged();
	double GetTemperature() const;
	double GetHumidity() const;
	double GetPressure() const;
	double GetWindSpeed() const;
	double GetWindDirecion() const;

protected:
	EventsData GetChangedData() const override;

private:
	EventsData CollectChangedWeatherData() const noexcept;
	WeatherInfo CreateTemperatureInfo() const noexcept;
	WeatherInfo CreateHumidityInfo() const noexcept;
	WeatherInfo CreatePressureInfo() const noexcept;
	WeatherInfo CreateWindSpeedInfo() const noexcept;
	WeatherInfo CreateWindDirectionInfo() const noexcept;

	ValueTracker<double> m_temperature{ 0.0 };
	ValueTracker<double> m_humidity{ 0.0 };
	ValueTracker<double> m_pressure{ 760.0 };
	ValueTracker<double> m_windSpeed{ 0.0 };
	ValueTracker<double> m_windDirection{ NaN };
};