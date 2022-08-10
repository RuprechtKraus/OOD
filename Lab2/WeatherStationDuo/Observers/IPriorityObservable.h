#pragma once
#include "IObservable.h"

template <typename T>
class IPriorityObservable : public IObservable<T>
{
public:
	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void SetObserverPriority(const IObserver<T>& observer, unsigned priority) = 0;
};
