#pragma once
#include "Observers/IObserver.h"
#include "StatisticsTrackers/ValueStatistics.h"
#include "StatisticsTrackers/CardinalDirectionStatistics.h"
#include "WeatherInfo.h"

class StatsDisplay : public IObserver<WeatherInfo>
{
public:
	StatsDisplay();

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(WeatherInfo const& data) override;
	void Display() const noexcept;

	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
	ValueStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
};