#pragma once
#include "Command/IRevertableCommand.h"
#include <memory>

class ICommandHistory
{
public:
	virtual void AddCommand(std::unique_ptr<IRevertableCommand>&& command) = 0;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual bool CanUndo() const = 0;
	virtual bool CanRedo() const = 0;
	virtual bool IsEmpty() const = 0;
	virtual bool IsFull() const = 0;

	virtual ~ICommandHistory() = default;
};