#include "CompressionOutputStream.h"

CompressionOutputStream::CompressionOutputStream(
	OutputStreamPtr&& stream, const ICompressor& compressor)
	: m_stream(std::move(stream))
	, m_compressor(compressor)
{
}

void CompressionOutputStream::WriteByte(uint8_t data)
{
	m_stream->WriteByte(data);
}

void CompressionOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	char* buffer = new char[1024];
	size_t gcount{ m_compressor.Compress(buffer, static_cast<const char*>(srcData), size) };
	m_stream->WriteBlock(buffer, gcount);
	delete[] buffer;
}