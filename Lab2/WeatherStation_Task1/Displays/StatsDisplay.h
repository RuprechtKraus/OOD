#pragma once
#include "Observers/IObserver.h"
#include "ValueStatistsics.h"
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

	ValueStatistsics m_temperatureStats;
	ValueStatistsics m_humidityStats;
	ValueStatistsics m_pressureStats;
};