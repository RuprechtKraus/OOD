#pragma once
#include "Observers/IObservable.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherInfo.h"
#include <unordered_map>

class StatsDisplay : public IObserver<WeatherInfo>
{
private:
	struct DataSourceStats
	{
		DataSourceStats(const IObservable<WeatherInfo>& wd, bool includeWindStats = true);

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
	std::string GetStationType(const IObservable<WeatherInfo>& observable) const;
	bool IsInsideStation(const IObservable<WeatherInfo>& observable) const noexcept;
	bool IsOutsideStation(const IObservable<WeatherInfo>& observable) const noexcept;

	DataSourceStats m_insideDataSource;
	DataSourceStats m_outsideDataSource;
};