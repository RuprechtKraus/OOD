#pragma once
#include "IObservable.h"
#include <set>

template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer) override
	{
		m_observers.insert(&observer);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		m_observers.erase(&observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		std::set<ObserverType*> observersCopy = m_observers;

		for (auto& observer : observersCopy)
		{
			observer->Update(data);
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};