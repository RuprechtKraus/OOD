#pragma once
#include "WeatherInfo.h"
#include <iostream>
#include <string>

template <typename T>
class IValueStatistics
{
public:
	virtual void AddEntry(const T& value) = 0;
	virtual void Display() const = 0;
};

class NumericStatistics : IValueStatistics<double>
{
public:
	NumericStatistics(const std::string& name, std::ostream& output = std::cout);

	void AddEntry(const double& value) noexcept override;
	void Display() const noexcept override;

private:
	std::string m_name;
	std::ostream& m_output;
	double m_minValue = std::numeric_limits<double>::infinity();
	double m_maxValue = -std::numeric_limits<double>::infinity();
	double m_accValue = 0;
	unsigned m_countAcc = 0;
};

class CardinalDirectionStatistics : IValueStatistics<WindInfo>
{
public:
	CardinalDirectionStatistics(const std::string& name, std::ostream& output = std::cout);

	void AddEntry(const WindInfo& windInfo) noexcept override;
	void Display() const noexcept override;

private:
	int GetAverage() const noexcept;
	static std::string DegreesToCardinalDirection(double degrees);
	static bool IsWithingDeviationRange(double value, double anchor,
		unsigned absoluteDeviation) noexcept;
	static double NormalizeDegrees(double degrees) noexcept;
	static double DegreesToRadians(double degrees) noexcept;
	static double RadiansToDegrees(double radians) noexcept;

	std::string m_name;
	std::ostream& m_output;
	double m_sinSum = 0;
	double m_cosSum = 0;
	unsigned m_countAcc = 0;
};