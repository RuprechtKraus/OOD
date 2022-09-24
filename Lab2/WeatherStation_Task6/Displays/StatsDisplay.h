#pragma once
#include "Observers/IObserver.h"
#include "StatisticsTrackers/CardinalDirectionStatistics.h"
#include "StatisticsTrackers/ValueStatistics.h"
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
	void Update(WeatherInfo const& data) override;
	void Display(WeatherStationType source) const noexcept;

	std::unordered_map<WeatherStationType, WeatherStatistics> m_sources;
};