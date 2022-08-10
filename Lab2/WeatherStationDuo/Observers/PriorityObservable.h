#pragma once
#include "IObserver.h"
#include "IPriorityObservable.h"
#include <cassert>
#include <set>
#include <stdexcept>

template <typename T, typename SubscriptionOptions>
struct ChangedData
{
	T data;
	SubscriptionOptions subOptions;
};

template <typename T, typename SubscriptionOptions>
class PriorityObservable : public IPriorityObservable<T, SubscriptionOptions>
{
public:
	using ObserverType = IObserver<T>;

private:
	struct ObserverInfo;
	using Observers = std::set<ObserverInfo, std::greater<ObserverInfo>>;
	using Iterator = typename Observers::iterator;

	struct ObserverInfo
	{
		ObserverInfo(ObserverType& observer, unsigned priority, SubscriptionOptions subOptions)
			: observer(&observer)
			, priority(priority)
			, subOptions(subOptions)
		{
		}

		bool operator>(const ObserverInfo& other) const
		{
			if (priority == other.priority)
			{
				return observer > other.observer;
			}
			return priority > other.priority;
		}

		ObserverType* observer;
		unsigned priority;
		SubscriptionOptions subOptions;
	};

public:
	PriorityObservable(const std::string& name);

public:
	void RegisterObserver(ObserverType& observer, SubscriptionOptions subOptions, unsigned priority = 0) override;
	void SetObserverPriority(const ObserverType& observer, unsigned priority) override;
	void RemoveObserver(ObserverType& observer) override;
	void NotifyObservers() const noexcept override;

protected:
	virtual ChangedData<T, SubscriptionOptions> GetChangedData(SubscriptionOptions subOptions) const = 0;

	Observers m_observers;

private:
	void ChangeObserverPiority(Iterator it, unsigned priority);
	Iterator FindObserver(const ObserverType& observer);

	const std::string m_name;
};

template <typename T, typename SubscriptionOptions>
PriorityObservable<T, SubscriptionOptions>::PriorityObservable(const std::string& name)
	: m_name(name)
{
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::RegisterObserver(
	ObserverType& observer, SubscriptionOptions subOptions, unsigned priority)
{
	auto it = FindObserver(observer);
	if (it == m_observers.end())
	{
		m_observers.emplace(observer, priority, subOptions);
	}
	else
	{
		ChangeObserverPiority(it, priority);
	}
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::SetObserverPriority(
	const ObserverType& observer, unsigned priority)
{
	auto it = FindObserver(observer);
	if (it != m_observers.end())
	{
		ChangeObserverPiority(it, priority);
	}
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::RemoveObserver(ObserverType& observer)
{
	auto it = FindObserver(observer);
	m_observers.erase(it);
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::ChangeObserverPiority(Iterator it, unsigned priority)
{
	ObserverInfo o = *it;
	o.priority = priority;
	o.subOptions = it->subOptions;
	m_observers.erase(it);
	m_observers.insert(m_observers.end(), std::move(o));
}

template <typename T, typename SubscriptionOptions>
typename PriorityObservable<T, SubscriptionOptions>::Iterator
PriorityObservable<T, SubscriptionOptions>::FindObserver(const ObserverType& observer)
{
	return std::find_if(m_observers.begin(), m_observers.end(), [&observer](const ObserverInfo& o) {
		return o.observer == &observer;
	});
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::NotifyObservers() const noexcept
{
	Observers observersCopy = m_observers;
	for (auto& observerInfo : observersCopy)
	{
		auto changedData = GetChangedData(observerInfo.subOptions);
		if (observerInfo.subOptions & changedData.subOptions)
		{
			observerInfo.observer->Update(m_name, changedData.data);
		}
	}
}