#pragma once
#include "Observers/IObserver.h"
#include "StatisticsTrackers/ValueStatistics.h"
#include "StatisticsTrackers/CardinalDirectionStatistics.h"
#include "WeatherInfo.h"

class StatsDisplay : public IObserver<WeatherInfo>
{
public:
	StatsDisplay();

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfo& data) override;
	void AddEntry(const WeatherInfo& data);
	void Display(WeatherEvent event) const;

	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
	ValueStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
};