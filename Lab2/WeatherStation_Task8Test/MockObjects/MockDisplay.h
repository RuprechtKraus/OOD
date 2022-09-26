#pragma once
#include "IWeatherStation.h"
#include "WeatherInfo.h"
#include <string>
#include <vector>

using namespace std::placeholders;

class MockDisplay
{
public:
	MockDisplay(
		IWeatherStation<WeatherInfo>& wd,
		const std::string& name,
		std::vector<std::string>* callSequence = nullptr)
		: m_name(name)
		, m_callSequence(callSequence)
	{
		m_connection = wd.DoOnWeatherDataChange(
			std::bind(&MockDisplay::Update, this), 0);
	}

	bool WasUpdated() const noexcept
	{
		return m_wasUpdated;
	}

	void Reset() noexcept
	{
		m_wasUpdated = false;
	}

private:
	void Update() noexcept
	{
		m_wasUpdated = true;
		if (m_callSequence)
		{
			m_callSequence->push_back(m_name);
		}
	}

	signals::scoped_connection m_connection;
	std::string m_name;
	std::vector<std::string>* m_callSequence;
	bool m_wasUpdated{ false };
};