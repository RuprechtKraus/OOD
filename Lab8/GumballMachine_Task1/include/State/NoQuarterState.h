#pragma once
#include "GumballMachine/IGumballMachine.h"
#include "IState.h"
#include <iostream>

class NoQuarterState : public IState
{
public:
	NoQuarterState(IGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
};