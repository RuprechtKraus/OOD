#pragma once
#include "ICommandHistory.h"
#include <vector>

class CommandHistory : public ICommandHistory
{
private:
	using Container = std::vector<std::unique_ptr<IRevertableCommand>>;

public:
	CommandHistory(unsigned size = 10);

	void AddCommand(std::unique_ptr<IRevertableCommand>&& command) override;
	void Undo() override;
	void Redo() override;
	bool IsEmpty() const noexcept override;
	bool IsFull() const noexcept override;

private:
	Container m_commands;
	unsigned m_size;
	unsigned m_index;
};