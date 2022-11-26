#pragma once
#include "GumballMachine/IGumballMachine.h"
#include "IState.h"
#include <iostream>

class SoldOutState : public IState
{
public:
	SoldOutState(IGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarter() override;
	void TurnCrank() override;
	void Dispense() override;

	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
};