#include "CardinalDirectionStatistics.h"
#include "Utilities/CardinalDirectionUtils.h"
#include <iostream>

CardinalDirectionStatistics::CardinalDirectionStatistics(const std::string& name)
	: m_valueName(name)
{
}

void CardinalDirectionStatistics::Update(const WindInfo& windInfo) noexcept
{
	double normalizedDegrees = NormalizeDegrees(windInfo.direction);
	m_sinSum += windInfo.speed * sin(DegreesToRadians(windInfo.direction));
	m_cosSum += windInfo.speed * cos(DegreesToRadians(windInfo.direction));
	m_countAcc++;
}

void CardinalDirectionStatistics::Display() const
{
	std::cout << "Average wind direction " << DegreesToCardinalDirection(GetAverage()) << std::endl;
	std::cout << "----------------" << std::endl;
}

int CardinalDirectionStatistics::GetAverage() const noexcept
{
	return (static_cast<int>(RadiansToDegrees(atan2(m_sinSum, m_cosSum))) + 360) % 360;
}