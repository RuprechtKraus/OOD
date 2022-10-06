#pragma once
#include <exception>

class EOFException : public std::exception
{
public:
	EOFException() noexcept
		: exception()
	{
	}

	explicit EOFException(const char* const message) noexcept
		: exception(message)
	{
	}
};