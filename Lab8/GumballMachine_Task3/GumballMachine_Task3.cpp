#include <iostream>
#include "GumballMachine/GumballMachineWithState.h"

int main()
{
	GumballMachineWithState machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.Refill(5);
	machine.TurnCrank();
}