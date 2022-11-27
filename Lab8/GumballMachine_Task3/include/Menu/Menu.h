#pragma once
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std::placeholders;

class Menu
{
public:
	using Command = std::function<void(std::istringstream& args)>;

private:
	struct Item
	{
		Item(const std::string& description, const Command& command);

		std::string description;
		Command command;
	};

public:
	void AddCommand(
		const std::string& shortcut,
		const std::string& description,
		const Command& command);

	void Run();
	void ShowHelp() const noexcept;
	void Exit() noexcept;

private:
	void ExecuteCommand(const std::string& shortcut, std::istringstream& args) const noexcept;

	std::unordered_map<std::string, Item> m_items{
		{ "exit", Item{ "Exit the program", [this](std::istringstream&) { Exit(); } } },
		{ "help", Item{ "Show command list", [this](std::istringstream&) { ShowHelp(); } } }
	};

	bool m_isRunning = true;
};