#pragma once
#include <string>

template <typename T>
class IObserver
{
public:
	virtual void Update(const std::string& source, const T& data) = 0;
	virtual ~IObserver() = default;
};