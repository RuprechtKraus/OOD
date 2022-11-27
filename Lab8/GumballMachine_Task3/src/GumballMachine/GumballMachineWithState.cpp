#include "GumballMachine/GumballMachineWithState.h"

GumballMachineWithState::GumballMachineWithState(unsigned numBalls)
	: m_ballCount(numBalls)
	, m_quarterCount(0)
{
	if (m_ballCount > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void GumballMachineWithState::EjectQuarters()
{
	m_currentState->EjectQuarters();
}

void GumballMachineWithState::InsertQuarter()
{
	m_currentState->InsertQuarter();
}

void GumballMachineWithState::TurnCrank()
{
	GumballMachineWithState::m_currentState->TurnCrank();
	GumballMachineWithState::m_currentState->Dispense();
}

std::string GumballMachineWithState::ToString() const
{
	auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{} and {} quarter{}
Machine is {}
)",
		m_ballCount, m_ballCount != 1 ? "s" : "",
		m_quarterCount, m_quarterCount != 1 ? "s" : "",
		m_currentState->ToString());

	return fmt;
}

bool GumballMachineWithState::AddQuarter()
{
	if (m_quarterCount != MAX_QUARTER_COUNT)
	{
		m_quarterCount++;
		return true;
	}
	return false;
}

bool GumballMachineWithState::ConsumeQuarter()
{
	if (m_quarterCount > 0)
	{
		m_quarterCount--;
		return true;
	}
	return false;
}

void GumballMachineWithState::ReleaseAllQuarters()
{
	m_quarterCount = 0;
}

unsigned GumballMachineWithState::GetQuarterCount() const
{
	return m_quarterCount;
}

void GumballMachineWithState::ReleaseBall()
{
	if (m_ballCount != 0)
	{
		std::cout << "A gumball comes rolling out the slot...\n";
		--m_ballCount;
	}
}

void GumballMachineWithState::Refill(unsigned count)
{
	m_currentState->Refill(count);
}

void GumballMachineWithState::AddBalls(unsigned count)
{
	m_ballCount += count;
}

unsigned GumballMachineWithState::GetBallCount() const
{
	return m_ballCount;
}

void GumballMachineWithState::SetSoldOutState()
{
	m_currentState.reset(new SoldOutState(*this));
}

void GumballMachineWithState::SetNoQuarterState()
{
	m_currentState.reset(new NoQuarterState(*this));
}

void GumballMachineWithState::SetSoldState()
{
	m_currentState.reset(new SoldState(*this));
}

void GumballMachineWithState::SetHasQuarterState()
{
	m_currentState.reset(new HasQuarterState(*this));
}