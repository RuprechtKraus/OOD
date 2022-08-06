#pragma once
#include "IObservable.h"
#include "IObserver.h"
#include "Observable.h"

class TestObservable : public Observable<int>
{
protected:
	int GetChangedData() const noexcept override
	{
		return m_data;
	}

private:
	int m_data{};
};

class UnsibscribeObserver : public IObserver<int>
{
	using Base = IObserver<int>;
	using Subject = IObservable<int>;

public:
	UnsibscribeObserver(Subject& subject)
		: m_subject(&subject)
	{
	}

	void Update(const int& data) const override
	{
		m_subject->RemoveObserver(const_cast<UnsibscribeObserver&>(*this));
	}

private:
	Subject* m_subject;
};

class UsualObserver : public IObserver<int>
{
	using Base = IObserver<int>;

public:
	void Update(const int& data) const override
	{
	}
};