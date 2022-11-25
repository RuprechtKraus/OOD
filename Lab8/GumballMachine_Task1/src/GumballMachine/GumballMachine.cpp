#include "GumballMachine/GumballMachine.h"

GumballMachine::GumballMachine(unsigned numBalls)
	: m_count(numBalls)
{
	if (m_count > 0)
	{
		SetNoQuarterState();
	}
	else
	{
		SetSoldOutState();
	}
}

void GumballMachine::EjectQuarter()
{
	m_currentState->EjectQuarter();
}

void GumballMachine::InsertQuarter()
{
	m_currentState->InsertQuarter();
}

void GumballMachine::TurnCrank()
{
	GumballMachine::m_currentState->TurnCrank();
	GumballMachine::m_currentState->Dispense();
}

std::string GumballMachine::ToString() const
{
	auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{}
Machine is {}
)",
		m_count, m_count != 1 ? "s" : "", m_currentState->ToString());

	return fmt;
}

unsigned GumballMachine::GetBallCount() const
{
	return m_count;
}

void GumballMachine::ReleaseBall()
{
	if (m_count != 0)
	{
		std::cout << "A gumball comes rolling out the slot...\n";
		--m_count;
	}
}

void GumballMachine::SetSoldOutState()
{
	m_currentState.reset(new SoldOutState(*this));
}

void GumballMachine::SetNoQuarterState()
{
	m_currentState.reset(new NoQuarterState(*this));
}

void GumballMachine::SetSoldState()
{
	m_currentState.reset(new SoldState(*this));
}

void GumballMachine::SetHasQuarterState()
{
	m_currentState.reset(new HasQuarterState(*this));
}