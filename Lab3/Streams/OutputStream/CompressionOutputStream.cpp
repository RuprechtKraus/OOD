#include "CompressionOutputStream.h"

CompressionOutputStream::CompressionOutputStream(OutputStreamPtr&& stream)
	: m_stream(std::move(stream))
{
}

void CompressionOutputStream::WriteByte(uint8_t data)
{
	m_stream->WriteByte(data);
}

void CompressionOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	char* buffer = new char[8192];
	//size_t gcount{ m_compressor->Compress(buffer, static_cast<const char*>(srcData), size) };
	//m_stream->WriteBlock(buffer, gcount);
	delete[] buffer;
}