#pragma once
#include "IObserver.h"
#include "IPriorityObservable.h"
#include <cassert>
#include <set>
#include <stdexcept>

template <typename T>
class PriorityObservable : public IPriorityObservable<T>
{
public:
	using ObserverType = IObserver<T>;

private:
	using ObserverPriority = std::pair<unsigned, ObserverType*>;
	using Observers = std::set<ObserverPriority, std::greater<ObserverPriority>>;
	using Iterator = typename Observers::iterator;

public:
	void RegisterObserver(unsigned priority, ObserverType& observer) override;
	void RegisterObserver(ObserverType& observer) override;
	void SetObserverPriority(unsigned priority, const ObserverType& observer) override;
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() const noexcept override;

protected:
	virtual T GetChangedData() const = 0;

	Observers m_observers;

private:
	void ChangeObserverPiority(unsigned priority, Iterator it);
	Iterator FindObserver(const ObserverType& observer);
};

template <typename T>
void PriorityObservable<T>::RegisterObserver(unsigned priority, ObserverType& observer)
{
	auto it = FindObserver(observer);
	if (it == m_observers.end())
	{
		m_observers.emplace_hint(m_observers.end(), priority, &observer);
	}
	else
	{
		ChangeObserverPiority(priority, it);
	}
}

template <typename T>
void PriorityObservable<T>::RegisterObserver(ObserverType& observer)
{
	RegisterObserver(0, observer);
}

template <typename T>
void PriorityObservable<T>::SetObserverPriority(unsigned priority, const ObserverType& observer)
{
	auto it = FindObserver(observer);
	if (it != m_observers.end())
	{
		ChangeObserverPiority(priority, it);
	}
}

template <typename T>
void PriorityObservable<T>::RemoveObserver(ObserverType& observer)
{
	m_observers.erase(FindObserver(observer));
}

template <typename T>
void PriorityObservable<T>::ChangeObserverPiority(unsigned priority, Iterator it)
{
	assert(it != m_observers.end());
	ObserverPriority o = *it;
	o.first = priority;
	m_observers.erase(it);
	m_observers.insert(m_observers.end(), std::move(o));
}

template <typename T>
typename PriorityObservable<T>::Iterator PriorityObservable<T>::FindObserver(const ObserverType& observer)
{
	return std::find_if(m_observers.begin(), m_observers.end(), [&observer](const ObserverPriority& o) {
		return o.second == &observer;
	});
}

template <typename T>
void PriorityObservable<T>::NotifyObservers() const noexcept
{
	std::set<ObserverPriority, std::greater<ObserverPriority>> observersCopy = m_observers;
	for (auto& observer : observersCopy)
	{
		observer.second->Update(GetChangedData());
	}
}
