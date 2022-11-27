#include "State/NoQuarterState.h"

NoQuarterState::NoQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void NoQuarterState::InsertQuarter()
{
	m_gumballMachine.AddQuarter();
	std::cout << "You inserted a quarter\n";
	m_gumballMachine.SetHasQuarterState();
}

void NoQuarterState::EjectQuarters()
{
	std::cout << "You haven't inserted a quarter\n";
}

void NoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter\n";
}

void NoQuarterState::Dispense()
{
	std::cout << "You need to pay first\n";
}

void NoQuarterState::Refill(unsigned count)
{
	if (count != 0)
	{
		std::cout << "Added " << count << " gumball(s)\n";
		m_gumballMachine.AddBalls(count);
	}
}

std::string NoQuarterState::ToString() const
{
	return "waiting for quarter";
}