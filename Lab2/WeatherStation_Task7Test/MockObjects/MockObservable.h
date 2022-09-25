#pragma once
#include "Observers/Observable.h"
#include "TestInfo.h"

class MockObservable : public Observable<TestInfo, TestEvent>
{
private:
	using Base = Observable<TestInfo, TestEvent>;
	using EventsData = Base::EventsData;

public:
	void ImitateEvent(TestEvent event)
	{
		m_event = event;
		NotifyObservers();
	}

protected:
	EventsData GetChangedData() const override
	{
		return std::unordered_map<TestEvent, TestInfo>{
			std::pair<TestEvent, TestInfo>(m_event, TestInfo{ m_event, 0 })
		};
	}

private:
	TestEvent m_event;
};