#include "StatsDisplay.h"
#include <format>

ValueStatistics::ValueStatistics(const std::string& name)
	: m_valueName(name)
{
}

void ValueStatistics::Update(double value) noexcept
{
	m_minValue = std::min(m_minValue, value);
	m_maxValue = std::max(m_maxValue, value);
	m_accValue += value;
	++m_countAcc;
}

void ValueStatistics::Display() const noexcept
{
	std::cout << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
	std::cout << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
	std::cout << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
	std::cout << "----------------" << std::endl;
}

void StatsDisplay::Update(WeatherInfo const& data) const
{
	m_staticData.at(m_temperatureDataName).get()->Update(data.temperature);
	m_staticData.at(m_humidityDataName).get()->Update(data.humidity);
	m_staticData.at(m_pressureDataName).get()->Update(data.pressure);
	Display();
}

void StatsDisplay::Display() const noexcept
{
	for (const auto& [_, data] : m_staticData)
	{
		data.get()->Display();
	}
}