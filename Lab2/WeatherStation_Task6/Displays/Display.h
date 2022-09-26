#pragma once
#include "Observers/IObservable.h"
#include "WeatherInfo.h"
#include <string>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(
		const IObservable<WeatherInfo>& insideSource,
		const IObservable<WeatherInfo>& outsideSource)
		: m_insideSource(insideSource)
		, m_outsideSource(outsideSource)
	{
	}

private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(const IObservable<WeatherInfo>& sender, WeatherInfo const& data) override;
	std::string GetStationType(const IObservable<WeatherInfo>& observable) const;
	bool IsInsideStation(const IObservable<WeatherInfo>& observable) const noexcept;
	bool IsOutsideStation(const IObservable<WeatherInfo>& observable) const noexcept;

	const IObservable<WeatherInfo>& m_insideSource;
	const IObservable<WeatherInfo>& m_outsideSource;
};
