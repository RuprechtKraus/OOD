#include "ValueStatistics.h"
#include <format>
#include <iostream>

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

void ValueStatistics::Display() const
{
	std::cout << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
	std::cout << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
	std::cout << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
	std::cout << "----------------" << std::endl;
}