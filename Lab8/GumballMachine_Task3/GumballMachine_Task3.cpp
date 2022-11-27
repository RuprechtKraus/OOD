#include "GumballMachine/GumballMachineWithState.h"
#include "Menu/Menu.h"
#include <iostream>

void InitMenu(Menu& menu, GumballMachineWithState& gumballMachine);

int main()
{
	Menu menu;
	GumballMachineWithState machine(5);

	InitMenu(menu, machine);
	menu.Run();
}
void InitMenu(Menu& menu, GumballMachineWithState& gumballMachine)
{
	menu.AddCommand("insertquarter", "Insert one quarter into the machine",
		[&gumballMachine](std::istringstream&) {
			gumballMachine.InsertQuarter();
		});
	menu.AddCommand("ejectquarters", "Eject all quarters from the machine",
		[&gumballMachine](std::istringstream&) {
			gumballMachine.EjectQuarters();
		});
	menu.AddCommand("turncrunk", "Turn the crunk to get a gumball",
		[&gumballMachine](std::istringstream&) {
			gumballMachine.TurnCrank();
		});
	menu.AddCommand("refill", "Refill the machine with gumballs. Usage: refill <count>",
		[&gumballMachine](std::istringstream& args) {
			unsigned count;
			if (!(args >> count))
			{
				throw std::invalid_argument("Invalid refill value");
			}
			gumballMachine.Refill(count);
		});
	menu.AddCommand("state", "Show the state of the machine",
		[&gumballMachine](std::istringstream&) {
			std::cout << gumballMachine.ToString();
		});
}