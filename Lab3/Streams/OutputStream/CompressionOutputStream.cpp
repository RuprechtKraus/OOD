#include "CompressionOutputStream.h"
#include <format>
#include <string>

CompressionOutputStream::CompressionOutputStream(OutputStreamPtr&& stream)
	: m_stream(std::move(stream))
{
}

void CompressionOutputStream::WriteByte(uint8_t data)
{
}

void CompressionOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	std::string compressedData{ Compress(srcData, size) };
	m_stream->WriteBlock(compressedData.c_str(), compressedData.size());
}

std::string CompressionOutputStream::Compress(const void* srcData, std::streamsize size)
{
	uint8_t byte{ static_cast<const uint8_t*>(srcData)[0] };
	uint8_t nextByte{};
	std::streamsize count{ 1 };
	std::string result;

	for (size_t i = 1; i <= size; i++)
	{
		nextByte = static_cast<const uint8_t*>(srcData)[i];

		if (nextByte == byte)
		{
			count++;
		}
		else
		{
			result += MakeByteInfo(byte, count);
			byte = nextByte;
			count = 1;
		}
	}

	return result;
}

std::string CompressionOutputStream::MakeByteInfo(uint8_t byte, size_t count)
{
	std::string result = "{";
	result += byte;
	result += ",";
	result += std::to_string(count);
	result += "}";

	return result;
}