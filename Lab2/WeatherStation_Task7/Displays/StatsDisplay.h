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
	void Update(const WeatherInfo& data) override;
	void AddEntry(const WeatherInfo& data);
	void Display(WeatherEvent event) const;

	ValueStatistics m_temperatureStats;
	ValueStatistics m_humidityStats;
	ValueStatistics m_pressureStats;
	ValueStatistics m_windSpeed;
	CardinalDirectionStatistics m_windDirection;
};