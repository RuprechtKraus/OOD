#include "CommandHistory.h"
#include <algorithm>
#include <stdexcept>

CommandHistory::CommandHistory(unsigned size)
	: m_size(size)
	, m_index(0)
{
}

void CommandHistory::AddCommand(std::unique_ptr<IRevertableCommand>&& command)
{
	m_commands.erase(m_commands.begin() + m_index, m_commands.end());
	m_index = m_commands.size();

	if (IsFull())
	{
		std::rotate(m_commands.begin(), m_commands.begin() + 1, m_commands.end());
		m_commands.back() = std::move(command);
	}
	else
	{
		m_commands.push_back(std::move(command));
		m_index++;
	}
}

void CommandHistory::Undo()
{
	if (!CanUndo())
	{
		throw std::logic_error("Unable to undo");
	}

	m_commands[--m_index]->Revert();
}

void CommandHistory::Redo()
{
	if (!CanRedo())
	{
		throw std::logic_error("Unable to redo");
	}

	m_commands[m_index++]->Execute();
}

bool CommandHistory::CanUndo() const noexcept
{
	return IsEmpty() || m_index == 0;
}

bool CommandHistory::CanRedo() const noexcept
{
	return m_index == m_commands.size();
}

bool CommandHistory::IsEmpty() const noexcept
{
	return m_commands.empty();
}

bool CommandHistory::IsFull() const noexcept
{
	return m_commands.size() == m_size;
}
