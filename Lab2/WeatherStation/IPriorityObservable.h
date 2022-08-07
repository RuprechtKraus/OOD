#pragma once
#include "IObservable.h"

template <typename T>
class IPriorityObservable : public IObservable<T>
{
public:
	virtual void RegisterObserver(unsigned priority, IObserver<T>& observer) = 0;
	virtual void SetObserverPriority(unsigned priority, const IObserver<T>& observer) = 0;
};
