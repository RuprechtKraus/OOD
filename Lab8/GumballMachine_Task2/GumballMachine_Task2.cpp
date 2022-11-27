#include <iostream>
#include "GumballMachine/GumballMachineWithState.h"
#include "GumballMachine/NaiveGumballMachine.h"

int main()
{
	NaiveGumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
}