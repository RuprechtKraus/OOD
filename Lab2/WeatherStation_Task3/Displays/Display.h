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
	void Update(WeatherInfo const& data) override;
};
