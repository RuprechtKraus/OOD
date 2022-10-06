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
	uint8_t byte{};

	if (!m_buffer.empty())
	{
		return GetNextBufferedByte();
	}

	try
	{
		VerifyAndSkipNextLexem('{', true);
	}
	catch (const EOFException&)
	{
		return -1;
	}

	byte = m_stream->ReadByte();
	VerifyAndSkipNextLexem(',');
	int count{ ReadBytesCount() - 1 };
	BufferByteNTimes(byte, count);

	return byte;
}

uint8_t DecompressionInputStream::GetNextBufferedByte() noexcept
{
	uint8_t byte = m_buffer.front();
	m_buffer.pop();

	return byte;
}

void DecompressionInputStream::BufferByteNTimes(uint8_t byte, int count)
{
	for (size_t i = 0; i < count; i++)
	{
		m_buffer.push(byte);
	}
}

void DecompressionInputStream::VerifyAndSkipNextLexem(uint8_t expectedLexem, bool throwOnEOF)
{
	uint8_t lexem{ m_stream->ReadByte() };

	if (throwOnEOF && m_stream->IsEOF())
	{
		throw EOFException();
	}

	if (lexem != expectedLexem)
	{
		throw std::ios_base::failure("Compressed file is corrupted");
	}
}

int DecompressionInputStream::ReadBytesCount()
{
	std::string countStr;
	uint8_t count{};
	uint8_t lexem{};

	while (lexem = m_stream->ReadByte(), lexem != '}')
	{
		if (!std::isdigit(lexem))
		{
			throw std::ios_base::failure("Compressed file is corrupted");
		}

		countStr += lexem;
	}

	count = std::stoi(countStr);

	if (count == 0)
	{
		throw std::ios_base::failure("Compressed file is corrupted");
	}

	return count;
}

std::streamsize DecompressionInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	uint8_t byte{};
	std::streamsize gcount{};
	char* buffer = new char[size];

	for (; gcount < size; gcount++)
	{
		byte = ReadByte();

		if (IsEOF())
		{
			break;
		}

		buffer[gcount] = byte;
	}

	std::memcpy(dstBuffer, buffer, gcount);
	delete[] buffer;

	return gcount;
}