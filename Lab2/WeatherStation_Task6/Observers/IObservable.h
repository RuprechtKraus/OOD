#pragma once

template <typename T>
class IObserver;

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, unsigned priority) = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
	virtual void NotifyObservers() = 0;
};

template <typename T>
class IObserver
{
public:
	virtual void Update(const IObservable<T>& sender, const T& data) = 0;
	virtual ~IObserver() = default;
};