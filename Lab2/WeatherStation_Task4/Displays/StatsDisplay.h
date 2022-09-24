#pragma once
#include "Observers/IObserver.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherInfo.h"
#include <unordered_map>

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const WeatherInfo& data) override;
	void Display(WeatherStationType source) const;

	std::unordered_map<WeatherStationType, WeatherStatistics> m_sources;
};