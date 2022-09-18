#pragma once
#include "IObservable.h"
#include <map>
#include <stdexcept>

template <class T>
class Observable : public IObservable<T>
{
public:
	using ObserverType = IObserver<T>;
	using ObserversContainer = std::multimap<int, ObserverType*, std::greater<int>>;

	void RegisterObserver(ObserverType& observer, unsigned priority = 0) override
	{
		if (DoesObserverExist(observer))
		{
			throw std::runtime_error("Observer already exists");
		}

		m_observers.emplace(priority, &observer);
	}

	void RemoveObserver(ObserverType& observer) override
	{
		auto it = FindObserverOrThrow(observer);
		m_observers.erase(it);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		ObserversContainer observersCopy = m_observers;

		for (auto& [_, observer] : observersCopy)
		{
			observer->Update(data);
		}
	}

	bool DoesObserverExist(const ObserverType& observer) const noexcept
	{
		return FindObserver(observer) != m_observers.end();
	}

protected:
	// Классы-наследники должны перегрузить данный метод,
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	using Iterator = ObserversContainer::iterator;
	using ConstIterator = ObserversContainer::const_iterator;

	Iterator FindObserver(const ObserverType& observer) noexcept
	{
		return std::ranges::find_if(m_observers, [&observer](const auto& v) {
			return v.second == &observer;
		});
	}

	ConstIterator FindObserver(const ObserverType& observer) const noexcept
	{
		return std::ranges::find_if(m_observers, [&observer](const auto& v) {
			return v.second == &observer;
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