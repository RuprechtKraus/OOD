#pragma once
#include <limits>
#include <string>

class ValueStatistics
{
public:
	ValueStatistics(const std::string& name);

	void Update(double value) noexcept;
	void Display() const;

private:
	std::string m_valueName;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};