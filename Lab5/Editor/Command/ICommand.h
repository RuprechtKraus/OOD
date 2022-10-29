#pragma once

class ICommand
{
public:
	virtual void Execute() = 0;
	virtual void Revert() = 0;
	virtual ~ICommand() = default;
};