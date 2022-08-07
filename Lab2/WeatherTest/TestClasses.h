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

class TestPriorityObservable : public PriorityObservable<int>
{
public:
	void ChangeData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

	size_t GetObserversCount() const noexcept
	{
		return m_observers.size();
	}

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

class ObserverWithOutput : public IObserver<int>
{
	using Base = IObserver<int>;

public:
	ObserverWithOutput(const std::string& name, std::ostream& os)
		: m_name(name)
		, m_output(os)
	{
	}

	void Update(const int& data) const override
	{
		m_output << m_name << " updated data to " << data << std::endl;
	}

private:
	std::string m_name;
	std::ostream& m_output;
};
