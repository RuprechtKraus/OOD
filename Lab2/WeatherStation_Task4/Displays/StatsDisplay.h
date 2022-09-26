#pragma once
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherInfo.h"
#include "WeatherData.h"

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	struct DataSourceStats
	{
		DataSourceStats(const IObservable<WeatherInfo>& wd)
			: source(wd)
		{
		}

		const IObservable<WeatherInfo>& source;
		WeatherStatistics stats;
	};

public:
	StatsDisplay(
		const IObservable<WeatherInfo>& insideSource, 
		const IObservable<WeatherInfo>& outsideSource);

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(const IObservable<WeatherInfo>& sender, const WeatherInfo& data) override;

	DataSourceStats m_insideDataSource;
	DataSourceStats m_outsideDataSource;
};