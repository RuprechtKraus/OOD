#pragma once
#include "Observers/IObservable.h"
#include "WeatherInfo.h"
#include <string>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(
		const IObservable<WeatherInfo>& insideSource, 
		const IObservable<WeatherInfo>& outsideSource)
		: m_insideSource(insideSource)
		, m_outsideSource(outsideSource)
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data) override;
	std::string GetStationType(const IObservable<WeatherInfo>& sender) const;

	const IObservable<WeatherInfo>& m_insideSource;
	const IObservable<WeatherInfo>& m_outsideSource;
};
