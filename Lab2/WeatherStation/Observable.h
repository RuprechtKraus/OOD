#pragma once
#include "IObservable.h"
#include <functional>
#include <set>

template <typename T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	void RegisterObserver(ObserverType& observer);
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() noexcept override;

protected:
	virtual T GetChangedData() const = 0;

private:
	std::set<ObserverType*> m_observers;
};

template<typename T>
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
void Observable<T>::NotifyObservers() noexcept
{
	T data = GetChangedData();
	for (auto& observer : m_observers)
	{
		observer->Update(data);
	}
}