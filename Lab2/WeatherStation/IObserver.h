#pragma once

template <typename T>
class IObserver
{
public:
	virtual void Update(const T& data) const = 0;
	virtual ~IObserver() = default;
};