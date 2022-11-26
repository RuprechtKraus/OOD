#include "State/SoldState.h"

SoldState::SoldState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void SoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball\n";
}

void SoldState::EjectQuarters()
{
	std::cout << "Sorry you already turned the crank\n";
}

void SoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball\n";
}

void SoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();

	if (m_gumballMachine.GetBallCount() == 0)
	{
		std::cout << "Oops, out of gumballs\n";
		m_gumballMachine.SetSoldOutState();

		if (m_gumballMachine.GetQuarterCount() > 0)
		{
			std::cout << "Ejecting quarters\n";
			m_gumballMachine.ReleaseAllQuarters();
		}
	}
	else if (m_gumballMachine.GetQuarterCount() == 0)
	{
		m_gumballMachine.SetNoQuarterState();
	}

	m_gumballMachine.SetHasQuarterState();
}

std::string SoldState::ToString() const
{
	return "Delivering a gumball";
}