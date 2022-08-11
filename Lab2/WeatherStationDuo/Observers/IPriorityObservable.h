#pragma once

template <typename T, typename Event>
class IPriorityObservable
{
public:
	using ObserverType = IObserver<T>;

	virtual ~IPriorityObservable() = default;
	virtual void RegisterObserver(ObserverType& observer, Event subOptions, unsigned priority) = 0;
	virtual void SetObserverPriority(const ObserverType& observer, unsigned priority) = 0;
	virtual void RemoveObserver(const ObserverType& observer) = 0;
	virtual void NotifyObservers() const = 0;
};
