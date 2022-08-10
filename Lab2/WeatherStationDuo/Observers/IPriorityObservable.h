#pragma once

template <typename T, typename SubscriptionOptions>
class IPriorityObservable
{
public:
	using ObserverType = IObserver<T>;

	virtual ~IPriorityObservable() = default;
	virtual void RegisterObserver(ObserverType& observer, SubscriptionOptions subOptions, unsigned priority) = 0;
	virtual void SetObserverPriority(const ObserverType& observer, unsigned priority) = 0;
	virtual void RemoveObserver(ObserverType& observer) = 0;
	virtual void NotifyObservers() const = 0;
};
