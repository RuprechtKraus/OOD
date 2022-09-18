#pragma once
#include "Observers/IObserver.h"
#include "ValueStatistics.h"
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
	void Update(WeatherInfo const& data) override;
	void Display() const noexcept;

	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
};