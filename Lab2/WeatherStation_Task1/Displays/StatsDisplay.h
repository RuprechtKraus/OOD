#pragma once
#include "Observers/IObserver.h"
#include "ValueStatistsics.h"
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

	ValueStatistsics m_temperatureStats;
	ValueStatistsics m_humidityStats;
	ValueStatistsics m_pressureStats;
};