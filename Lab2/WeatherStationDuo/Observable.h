#pragma once
#include "IObservable.h"
#include <set>
#include <string>

template <typename T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;

	Observable(const std::string& name);

	std::string GetName() const noexcept;
	void RegisterObserver(ObserverType& observer) override;
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() const noexcept override;

protected:
	virtual T GetChangedData() const = 0;

	std::string m_name;
	std::set<ObserverType*> m_observers;
};

template <typename T>
Observable<T>::Observable(const std::string& name)
	: m_name(name)
{
}

template <typename T>
std::string Observable<T>::GetName() const noexcept
{
	return m_name;
}

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
		observer->Update(m_name, GetChangedData());
	}
}