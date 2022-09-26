#pragma once
#include "Observers/IObservable.h"
#include "WeatherInfo.h"
#include "WeatherData.h"

enum class StationType
{
	INSIDE,
	OUTSIDE
};

class MockObserver : public IObserver<WeatherInfo>
{
public:
	MockObserver(
		const IObservable<WeatherInfo>& insideSource,
		const IObservable<WeatherInfo>& outsideSource)
		: m_insideSource(insideSource)
		, m_outsideSource(outsideSource)
	{
	}

	void Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data) override
	{
		if (&sender == &m_insideSource)	
		{
			m_sourceType = StationType::INSIDE;
		}
		else if (&sender == &m_outsideSource)
		{
			m_sourceType = StationType::OUTSIDE;
		}
	}

	StationType GetLastSourceType() const noexcept
	{
		return m_sourceType;
	}

private:
	const IObservable<WeatherInfo>& m_insideSource;
	const IObservable<WeatherInfo>& m_outsideSource;
	StationType m_sourceType{};
};