#include "ValueStatistsics.h"
#include <format>
#include <iostream>

ValueStatistsics::ValueStatistsics(const std::string& name)
	: m_valueName(name)
{
}

void ValueStatistsics::Update(double value) noexcept
{
	m_minValue = std::min(m_minValue, value);
	m_maxValue = std::max(m_maxValue, value);
	m_accValue += value;
	++m_countAcc;
}

void ValueStatistsics::Display() const noexcept
{
	std::cout << std::format("Max {} ", m_valueName) << m_maxValue << std::endl;
	std::cout << std::format("Min {} ", m_valueName) << m_minValue << std::endl;
	std::cout << std::format("Average {} ", m_valueName) << (m_accValue / m_countAcc) << std::endl;
	std::cout << "----------------" << std::endl;
}