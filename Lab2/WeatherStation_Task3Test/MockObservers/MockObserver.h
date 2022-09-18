#pragma once
#include "MockObservable.h"
#include "Observers/IObserver.h"
#include <string>
#include <vector>

class MockObserver : public IObserver<int>
{
public:
	MockObserver(const std::string& name, std::vector<std::string>* callSequence = nullptr)
		: m_name(name)
		, m_callSequence(callSequence)
	{
	}

	int GetValue() const noexcept
	{
		return m_value;
	}

private:
	void Update(const int& data) override
	{
		m_value = data;
		if (m_callSequence)
		{
			m_callSequence->push_back(m_name);
		}
	}

	std::string m_name;
	std::vector<std::string>* m_callSequence;
	int m_value{ 0 };
};