#pragma once
#include "Observers/Observable.h"

class MockObservable : public Observable<int>
{
public:
	void SetValue(int value) noexcept
	{
		m_value = value;
		NotifyObservers();
	}

protected:
	int GetChangedData() const override
	{
		return m_value;
	}

private:
	int m_value{ 0 };
};