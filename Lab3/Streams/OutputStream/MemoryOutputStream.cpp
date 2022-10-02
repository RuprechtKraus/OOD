#include "MemoryOutputStream.h"

MemoryOutputStream::MemoryOutputStream(std::vector<uint8_t>& buffer)
	: m_buffer(buffer)
{
}

void MemoryOutputStream::WriteByte(uint8_t data)
{
	m_buffer.push_back(data);
}

void MemoryOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(static_cast<const uint8_t*>(srcData)[i]);
	}
}