#pragma once
#include <stdexcept>

template <typename T>
class ValueTracker
{
public:
	ValueTracker();
	explicit ValueTracker(const T& value);
	explicit ValueTracker(T&& value);

	void UpdateValue(const T& newValue);
	void UpdateValue(T&& newValue);
	void Reset() noexcept;
	bool IsChanged() const noexcept;
	T GetValue() const;

	operator T() const;

private:
	T m_value;
	bool m_isChanged;
	bool m_isEmpty;
};

template <typename T>
ValueTracker<T>::ValueTracker()
	: m_value(T())
	, m_isChanged(false)
	, m_isEmpty(true)
{
}

template <typename T>
ValueTracker<T>::ValueTracker(const T& value)
	: m_value(value)
	, m_isChanged(false)
	, m_isEmpty(true)
{
}

template <typename T>
ValueTracker<T>::ValueTracker(T&& value)
	: m_value(std::exchange(value, T()))
	, m_isChanged(false)
	, m_isEmpty(true)
{
}

template <typename T>
void ValueTracker<T>::UpdateValue(const T& newValue)
{
	if (m_isEmpty)
	{
		m_value = newValue;
		m_isChanged = true;
		m_isEmpty = false;
	}
	else if (m_value != newValue)
	{
		m_value = newValue;
		m_isChanged = true;
	}
	else
	{
		m_isChanged = false;
	}
}

template <typename T>
void ValueTracker<T>::UpdateValue(T&& newValue)
{
	if (m_value != newValue)
	{
		std::swap(m_value, newValue);
		m_isChanged = true;
	}
	else
	{
		m_isChanged = false;
	}
}

template <typename T>
void ValueTracker<T>::Reset() noexcept
{
	m_value = T();
	m_isChanged = false;
	m_isEmpty	 = true;
}

template <typename T>
bool ValueTracker<T>::IsChanged() const noexcept
{
	return m_isChanged;
}

template <typename T>
T ValueTracker<T>::GetValue() const
{
	return m_value;
}

template <typename T>
ValueTracker<T>::operator T() const
{
	return m_value;
}