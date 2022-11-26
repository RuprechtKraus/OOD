#pragma once
#include "GumballMachine/IGumballMachine.h"
#include "State/IState.h"
#include <iostream>

class SoldState : public IState
{
public:
	SoldState(IGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarters() override;
	void TurnCrank() override;
	void Dispense() override;

	std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
};