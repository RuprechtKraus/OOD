#pragma once
#include "IObservable.h"
#include <map>
#include <unordered_map>
#include <stdexcept>

template <typename T, typename E>
class Observable : public IObservable<T, E>
{
public:
	using ObserverType = IObserver<T>;
	using EventsData = std::unordered_map<E, T>;

private:
	struct ObserverInfo
	{
		ObserverInfo(ObserverType& observer, E events)
			: observer(&observer)
			, events(events)
		{
		}

		ObserverType* observer;
		E events;
	};

public:
	using ObserversContainer = std::multimap<int, ObserverInfo, std::greater<int>>;

	void RegisterObserver(ObserverType& observer, E events, unsigned priority = 0) override
	{
		if (DoesObserverExist(observer))
		{
			throw std::runtime_error("Observer already exists");
		}

		m_observers.emplace(priority, ObserverInfo(observer, events));
	}

	void SubscribeObserverToEvents(ObserverType& observer, E events)
	{
		auto it = FindObserverOrThrow(observer);
		it->second.events |= events;
	}

	void UnsubscribeObserverFromEvents(ObserverType& observer, E events)
	{
		auto it = FindObserverOrThrow(observer);
		it->second.events &= ~events;
		if (it->second.events == 0)
		{
			RemoveObserver(observer);
		}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto it = FindObserverOrThrow(observer);
		m_observers.erase(it);
	}

	void NotifyObservers() override
	{
		EventsData data = GetChangedData();
		ObserversContainer observersCopy = m_observers;

		for (auto& [_, observerInfo] : observersCopy)
		{
			for (const auto& [event, data] : data)
			{
				if (observerInfo.events & event)
				{
					observerInfo.observer->Update(data);
				}
			}
		}
	}

	bool DoesObserverExist(const ObserverType& observer) const noexcept
	{
		return FindObserver(observer) != m_observers.end();
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual EventsData GetChangedData() const = 0;

private:
	using Iterator = ObserversContainer::iterator;
	using ConstIterator = ObserversContainer::const_iterator;

	Iterator FindObserver(const ObserverType& observer) noexcept
	{
		return std::ranges::find_if(m_observers, [&observer](const auto& v) {
			return v.second.observer == &observer;
		});
	}

	ConstIterator FindObserver(const ObserverType& observer) const noexcept
	{
		return std::ranges::find_if(m_observers, [&observer](const auto& v) {
			return v.second.observer == &observer;
		});
	}

	Iterator FindObserverOrThrow(ObserverType& observer)
	{
		auto it = FindObserver(observer);

		if (it == m_observers.end())
		{
			throw std::runtime_error("Observer doesn't exist");
		}

		return it;
	}

	ObserversContainer m_observers;
};