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

	PriorityObservable(const std::string& name);

private:
	using ObserverInfo = std::pair<unsigned, ObserverType*>;
	using Observers = std::set<ObserverInfo, std::greater<ObserverInfo>>;
	using Iterator = typename Observers::iterator;

public:
	void RegisterObserver(ObserverType& observer, unsigned priority) override;
	void RegisterObserver(ObserverType& observer) override;
	void SetObserverPriority(const ObserverType& observer, unsigned priority) override;
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() const noexcept override;

protected:
	virtual T GetChangedData() const = 0;

	Observers m_observers;

private:
	void ChangeObserverPiority(Iterator it, unsigned priority);
	Iterator FindObserver(const ObserverType& observer);

	const std::string m_name;
};

template <typename T>
PriorityObservable<T>::PriorityObservable(const std::string& name)
	: m_name(name)
{
}

template <typename T>
void PriorityObservable<T>::RegisterObserver(ObserverType& observer, unsigned priority)
{
	auto it = FindObserver(observer);
	if (it == m_observers.end())
	{
		m_observers.emplace_hint(m_observers.end(), priority, &observer);
	}
	else
	{
		ChangeObserverPiority(it, priority);
	}
}

template <typename T>
void PriorityObservable<T>::RegisterObserver(ObserverType& observer)
{
	RegisterObserver(observer, 0);
}

template <typename T>
void PriorityObservable<T>::SetObserverPriority(const ObserverType& observer, unsigned priority)
{
	auto it = FindObserver(observer);
	if (it != m_observers.end())
	{
		ChangeObserverPiority(it, priority);
	}
}

template <typename T>
void PriorityObservable<T>::RemoveObserver(ObserverType& observer)
{
	auto it = FindObserver(observer);
	assert(it != m_observers.end());
	m_observers.erase(it);
}

template <typename T>
void PriorityObservable<T>::ChangeObserverPiority(Iterator it, unsigned priority)
{
	assert(it != m_observers.end());
	ObserverInfo o = *it;
	o.first = priority;
	m_observers.erase(it);
	m_observers.insert(m_observers.end(), std::move(o));
}

template <typename T>
typename PriorityObservable<T>::Iterator PriorityObservable<T>::FindObserver(const ObserverType& observer)
{
	return std::find_if(m_observers.begin(), m_observers.end(), [&observer](const ObserverInfo& o) {
		return o.second == &observer;
	});
}

template <typename T>
void PriorityObservable<T>::NotifyObservers() const noexcept
{
	std::set<ObserverInfo, std::greater<ObserverInfo>> observersCopy = m_observers;
	for (auto& observer : observersCopy)
	{
		observer.second->Update(m_name, GetChangedData());
	}
}
