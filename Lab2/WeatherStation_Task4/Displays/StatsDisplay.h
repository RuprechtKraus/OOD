#pragma once
#include "Observers/IObserver.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherInfo.h"
#include <unordered_map>

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(const WeatherInfo& data) override;
	void Display(WeatherStationType source) const;

	std::unordered_map<WeatherStationType, WeatherStatistics> m_sources;
};