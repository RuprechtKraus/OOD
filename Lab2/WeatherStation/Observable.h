#pragma once
#include "IObservable.h"
#include <functional>
#include <set>

template <typename T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer) override;
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() const noexcept override;

protected:
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};

template <typename T>
void Observable<T>::RegisterObserver(ObserverType& observer)
{
	m_observers.insert(&observer);
}

template <typename T>
void Observable<T>::RemoveObserver(ObserverType& observer)
{
	m_observers.erase(&observer);
}

template <typename T>
void Observable<T>::NotifyObservers() const noexcept
{
	std::set<ObserverType*> observersCopy = m_observers;
	for (auto& observer : observersCopy)
	{
		observer->Update(GetChangedData());
	}
}