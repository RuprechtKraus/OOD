#pragma once
#include "IObserver.h"

template <typename T, typename E>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, E events, unsigned priority) = 0;
	virtual void SubscribeObserverToEvents(IObserver<T>& observer, E events) = 0;
	virtual void UnsubscribeObserverFromEvents(IObserver<T>& observer, E events) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};