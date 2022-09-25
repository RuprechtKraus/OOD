#pragma once
#include "Observers/IObserver.h"
#include "TestInfo.h"

class MockObserver : public IObserver<TestInfo>
{
public:
	bool WasUpdated() const noexcept
	{
		return m_wasUpdated;
	}

	void Reset() noexcept
	{
		m_wasUpdated = false;
	}

private:
	void Update(const TestInfo& info) override
	{
		m_wasUpdated = true;
	}

	bool m_wasUpdated{ false };
};