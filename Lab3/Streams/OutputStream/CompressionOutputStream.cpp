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

	if (m_block.byte == data && m_block.count < std::numeric_limits<uint8_t>::max())
	{
		m_block.count++;
		return;
	}

	Flush();

	m_block = { data, 1 };
}

void CompressionOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto srcPtr = static_cast<const uint8_t*>(srcData);

	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(srcPtr[i]);
	}
}

void CompressionOutputStream::Flush()
{
	m_stream->WriteByte(m_block.byte);
	m_stream->WriteByte(m_block.count);

	m_block = {};
}