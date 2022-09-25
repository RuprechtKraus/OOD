#pragma once
#include "Observers/IObserver.h"
#include "WeatherInfo.h"

class Display : public IObserver<WeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
		������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
		�������� ���������
	*/
	void Update(const WeatherInfo& data) override;
	static void DisplayValue(const WeatherInfo& data);
};
