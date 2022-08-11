#pragma once
#include "IObserver.h"
#include "IPriorityObservable.h"
#include <map>
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
	//using Observers = std::set<ObserverInfo, std::greater<ObserverInfo>>;
	using Observers = std::multimap<int, ObserverInfo, std::greater<int>>;
	using Iterator = typename Observers::iterator;

	struct ObserverInfo
	{
		ObserverInfo(ObserverType& observer, SubscriptionOptions subOptions)
			: observer(&observer)
			, subOptions(subOptions)
		{
		}

		ObserverType* observer;
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
		m_observers.emplace(priority, ObserverInfo(observer, subOptions));
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
	auto node = m_observers.extract(it);
	node.key() = priority;
	m_observers.insert(std::move(node));
}

template <typename T, typename SubscriptionOptions>
typename PriorityObservable<T, SubscriptionOptions>::Iterator
PriorityObservable<T, SubscriptionOptions>::FindObserver(const ObserverType& observer)
{
	return std::ranges::find_if(m_observers, [&observer](const auto& v) {
		return v.second.observer == &observer;
	});
}

template <typename T, typename SubscriptionOptions>
void PriorityObservable<T, SubscriptionOptions>::NotifyObservers() const noexcept
{
	Observers observersCopy = m_observers;
	for (const auto& [_, observerInfo] : observersCopy)
	{
		auto changedData = GetChangedData(observerInfo.subOptions);
		if (observerInfo.subOptions & changedData.subOptions)
		{
			observerInfo.observer->Update(m_name, changedData.data);
		}
	}
}