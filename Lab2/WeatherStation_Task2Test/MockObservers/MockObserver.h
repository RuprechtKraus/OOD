#pragma once
#include "MockObservable.h"
#include "Observers/IObserver.h"

class MockObserver : public IObserver<int>
{
public:
	MockObserver(MockObservable& observable)
		: m_observable(observable)
	{
	}

	int GetValue() const noexcept
	{
		return m_value;
	}

private:
	void Update(const int& data) override
	{
		m_value = data;
		m_observable.RemoveObserver(*this);
	}

	MockObservable& m_observable;
	int m_value{ 0 };
};