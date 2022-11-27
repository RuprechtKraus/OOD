#include <iostream>
#include "GumballMachine/GumballMachineWithState.h"

int main()
{
	GumballMachineWithState machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
}