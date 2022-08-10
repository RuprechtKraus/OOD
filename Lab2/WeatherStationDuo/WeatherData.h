#pragma once
#include "Helpers/ValueTracker.h"
#include "Observers/PriorityObservable.h"
#include "WeatherInfo.h"
#include "WeatherStationLocation.h"

class WeatherData : public PriorityObservable<WeatherInfo, WeatherEvents>
{
public:
	WeatherData(const std::string& name, WeatherStationLocation location);

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
	ChangedData<WeatherInfo, WeatherEvents> GetChangedData(WeatherEvents eventsToDisplay) const noexcept override;

private:
	WeatherEvents CollectChangedWeatherParameters() const noexcept;

	WeatherStationLocation m_stationLocation;
	ValueTracker<double> m_temperature;
	ValueTracker<double> m_humidity;
	ValueTracker<double> m_pressure;
	ValueTracker<double> m_windSpeed;
	ValueTracker<double> m_windDirection;
};