#pragma once

template <typename T, typename Event>
class IPriorityObservable
{
public:
	using ObserverType = IObserver<T>;

	virtual ~IPriorityObservable() = default;
	virtual void RegisterObserver(ObserverType& observer, Event subOptions, unsigned priority) = 0;
	virtual void SetObserverPriority(ObserverType& observer, unsigned priority) = 0;
	virtual void RemoveObserver(ObserverType& observer) = 0;
	virtual void NotifyObservers() const = 0;
};
