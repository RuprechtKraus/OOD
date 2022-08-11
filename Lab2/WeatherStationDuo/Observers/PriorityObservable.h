#pragma once
#include "IObserver.h"
#include "IPriorityObservable.h"
#include <map>
#include <stdexcept>
#include <unordered_map>

template <typename T, typename Event>
class PriorityObservable : public IPriorityObservable<T, Event>
{
public:
	using ObserverType = IObserver<T>;
	using EventData = std::unordered_map<Event, T>;

private:
	struct ObserverInfo;
	using Observers = std::multimap<int, ObserverInfo, std::greater<int>>;
	using Iterator = typename Observers::iterator;
	using ConstIterator = typename Observers::const_iterator;

	struct ObserverInfo
	{
		ObserverInfo(ObserverType& observer, Event events)
			: observer(&observer)
			, events(events)
		{
		}

		ObserverType* observer;
		Event events;
	};

public:
	PriorityObservable(const std::string& name);
	void RegisterObserver(ObserverType& observer, Event events, unsigned priority = 0) override;
	void SetObserverPriority(const ObserverType& observer, unsigned priority) override;
	void RemoveObserver(const ObserverType& observer) override;
	void SubscribeObserverToEvents(const ObserverType& observer, Event events);
	void UnsubscribeObserverFromEvents(const ObserverType& observer, Event events);
	bool DoesObserverExist(const ObserverType& observer) const noexcept;

protected:
	virtual EventData GetChangedData() const = 0;
	void NotifyObservers() const noexcept override;

	std::string m_name;
	Observers m_observers;

private:
	void ChangeObserverPiority(Iterator it, unsigned priority);
	Iterator FindObserver(const ObserverType& observer) noexcept;
	ConstIterator FindObserver(const ObserverType& observer) const noexcept;
	Iterator FindObserverOrThrow(const ObserverType& observer);
};

template <typename T, typename Event>
PriorityObservable<T, Event>::PriorityObservable(const std::string& name)
	: m_name(name)
{
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::RegisterObserver(
	ObserverType& observer, Event events, unsigned priority)
{
	auto it = FindObserver(observer);
	if (it == m_observers.end())
	{
		m_observers.emplace(priority, ObserverInfo(observer, events));
	}
	else
	{
		ChangeObserverPiority(it, priority);
	}
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::SetObserverPriority(
	const ObserverType& observer, unsigned priority)
{
	auto it = FindObserverOrThrow(observer);
	ChangeObserverPiority(it, priority);
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::RemoveObserver(const ObserverType& observer)
{
	auto it = FindObserverOrThrow(observer);
	m_observers.erase(it);
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::ChangeObserverPiority(Iterator it, unsigned priority)
{
	auto node = m_observers.extract(it);
	node.key() = priority;
	m_observers.insert(std::move(node));
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::SubscribeObserverToEvents(
	const ObserverType& observer, Event events)
{
	auto it = FindObserverOrThrow(observer);
	it->second.events &= events;
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::UnsubscribeObserverFromEvents(
	const ObserverType& observer, Event events)
{
	auto it = FindObserverOrThrow(observer);
	it->second.events &= ~events;
	if (it->second.events == 0)
	{
		RemoveObserver(observer);
	}
}

template <typename T, typename Event>
bool PriorityObservable<T, Event>::DoesObserverExist(
	const ObserverType& observer) const noexcept
{
	return FindObserver(observer) != m_observers.end();
}


template <typename T, typename Event>
typename PriorityObservable<T, Event>::Iterator
PriorityObservable<T, Event>::FindObserver(const ObserverType& observer) noexcept
{
	return std::ranges::find_if(m_observers, [&observer](const auto& v) {
		return v.second.observer == &observer;
	});
}

template <typename T, typename Event>
typename PriorityObservable<T, Event>::ConstIterator
PriorityObservable<T, Event>::FindObserver(const ObserverType& observer) const noexcept
{
	return std::ranges::find_if(m_observers, [&observer](const auto& v) {
		return v.second.observer == &observer;
	});
}

template <typename T, typename Event>
typename PriorityObservable<T, Event>::Iterator
PriorityObservable<T, Event>::FindObserverOrThrow(const ObserverType& observer)
{
	auto it = FindObserver(observer);
	if (it == m_observers.end())
	{
		throw std::logic_error("Observer doesn't exist");
	}
	return it;
}

template <typename T, typename Event>
void PriorityObservable<T, Event>::NotifyObservers() const noexcept
{
	Observers observersCopy = m_observers;
	EventData changedData = GetChangedData();
	for (const auto& [_, observerInfo] : observersCopy)
	{
		for (const auto& [event, data] : changedData)
		{
			if (observerInfo.events & event)
			{
				observerInfo.observer->Update(data);
			}
		}
	}
}