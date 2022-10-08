#include "MemoryInputStream.h"

MemoryInputStream::MemoryInputStream(const std::vector<uint8_t>& buffer)
	: m_buffer(buffer)
{
}

MemoryInputStream::MemoryInputStream(std::vector<uint8_t>&& buffer)
	: m_buffer(std::move(buffer))
{
}

bool MemoryInputStream::IsEOF() const
{
	return m_position >= m_buffer.size();
}

std::uint8_t MemoryInputStream::ReadByte()
{
	if (IsEOF())
	{
		return '\0';
	}

	return m_buffer[m_position++];
}

std::streamsize MemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	if (IsEOF())
	{
		return '\0';
	}

	size_t bufferSize{ m_buffer.size() };
	std::streamsize gcount{};

	for (; m_position < bufferSize && gcount < size; m_position++)
	{
		static_cast<uint8_t*>(dstBuffer)[gcount] = m_buffer[m_position];
		gcount++;
	}

	return gcount;
}