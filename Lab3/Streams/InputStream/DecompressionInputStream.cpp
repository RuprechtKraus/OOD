#include "DecompressionInputStream.h"
#include "Exceptions/EOFException.h"
#include <string>

DecompressionInputStream::DecompressionInputStream(InputStreamPtr&& stream)
	: m_stream(std::move(stream))
{
}

bool DecompressionInputStream::IsEOF() const
{
	return m_stream->IsEOF();
}

std::uint8_t DecompressionInputStream::ReadByte()
{
	if (m_block.count == 0)
	{
		m_stream->ReadBlock(static_cast<void*>(&m_block.byte), sizeof(uint8_t));
		m_stream->ReadBlock(static_cast<void*>(&m_block.count), sizeof(int));
	}

	m_block.count--;

	return m_block.byte;
}

std::streamsize DecompressionInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	char* bufferPtr{ static_cast<char*>(dstBuffer) };
	uint8_t byte{};
	std::streamsize gcount{};

	for (; gcount < size; gcount++)
	{
		byte = ReadByte();

		if (IsEOF())
		{
			break;
		}

		bufferPtr[gcount] = byte;
	}

	return gcount;
}