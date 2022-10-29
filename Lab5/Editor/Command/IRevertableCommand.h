#pragma once

class IRevertableCommand
{
public:
	virtual void Execute() = 0;
	virtual void Revert() = 0;
	virtual ~IRevertableCommand() = default;
};