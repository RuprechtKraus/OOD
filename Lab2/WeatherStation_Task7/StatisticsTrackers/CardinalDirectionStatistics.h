#pragma once
#include "WeatherInfo.h"
#include <string>

class CardinalDirectionStatistics
{
public:
	CardinalDirectionStatistics(const std::string& name);

	void Update(const WindInfo& windInfo) noexcept;
	void Display() const;

private:
	int GetAverage() const noexcept;

	std::string m_valueName;
	double m_sinSum = 0;
	double m_cosSum = 0;
	unsigned m_countAcc = 0;
};