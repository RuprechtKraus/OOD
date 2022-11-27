#include "Menu/Menu.h"
#include <iostream>

Menu::Item::Item(const std::string& description, const Command& command)
	: description(description)
	, command(command)
{
}

void Menu::AddCommand(
	const std::string& shortcut,
	const std::string& description,
	const Command& command)
{
	m_items.emplace(std::pair(shortcut, Item{ description, command }));
}

void Menu::Run()
{
	ShowHelp();

	std::string command;
	std::string shortcut;
	std::istringstream args;

	while (m_isRunning && (std::cout << ">") && std::getline(std::cin, command))
	{
		args = std::istringstream(command);
		args >> shortcut;
		ExecuteCommand(shortcut, args);
		std::cout << std::endl;
	}
}

void Menu::ShowHelp() const noexcept
{
	std::cout << "Command list:\n";
	for (auto& [name, item] : m_items)
	{
		std::cout << name << ": " << item.description << std::endl;
	}
}

void Menu::Exit() noexcept
{
	m_isRunning = false;
}

void Menu::ExecuteCommand(const std::string& shortcut, std::istringstream& args) const noexcept
{
	try
	{
		m_items.at(shortcut).command(args);
	}
	catch (const std::out_of_range&)
	{
		std::cout << "Unknown command" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}