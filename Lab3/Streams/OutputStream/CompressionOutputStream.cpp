#include "CompressionOutputStream.h"
#include <format>
#include <string>

CompressionOutputStream::CompressionOutputStream(OutputStreamPtr&& stream)
	: m_stream(std::move(stream))
{
}

CompressionOutputStream::~CompressionOutputStream()
{
	Flush();
}

void CompressionOutputStream::WriteByte(uint8_t data)
{
	if (m_block.count == 0)
	{
		m_block = { data, 1 };
		return;
	}

	if (m_block.byte == data)
	{
		m_block.count++;
		return;
	}

	Flush();
	m_block = { data, 1 };
}

void CompressionOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	const uint8_t* srcPtr{ static_cast<const uint8_t*>(srcData) };
	uint8_t byte{ static_cast<const uint8_t*>(srcData)[0] };
	uint8_t nextByte{};
	std::streamsize count{ 1 };
	Block block{};

	for (size_t i = 1; i <= size; i++)
	{
		nextByte = srcPtr[i];

		if (nextByte == byte)
		{
			count++;
		}
		else
		{
			block.byte = byte;
			block.count = count;

			m_stream->WriteBlock(static_cast<const void*>(&block), sizeof(block));

			byte = nextByte;
			count = 1;
		}
	}
}

void CompressionOutputStream::Flush()
{
	m_stream->WriteBlock((const void*)(&m_block.byte), sizeof(uint8_t));
	m_stream->WriteBlock((const void*)(&m_block.count), sizeof(int));

	m_block = {};
}