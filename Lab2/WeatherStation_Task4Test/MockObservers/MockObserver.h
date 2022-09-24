#pragma once
#include "Observers/IObserver.h"
#include "WeatherInfo.h"

class MockObserver : public IObserver<WeatherInfo>
{
public:
	void Update(const WeatherInfo& data) override
	{
		m_sourceType = data.stationType;
	}

	WeatherStationType GetLastSourceType() const noexcept
	{
		return m_sourceType;
	}

private:
	WeatherStationType m_sourceType;
};