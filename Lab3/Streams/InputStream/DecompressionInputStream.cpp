#include "DecompressionInputStream.h"

DecompressionInputStream::DecompressionInputStream(
	InputStreamPtr&& stream, std::unique_ptr<ICompressor>&& compressor)
	: m_stream(std::move(stream))
	, m_compressor(std::move(compressor))
{
}

bool DecompressionInputStream::IsEOF() const
{
	return m_stream->IsEOF();
}

std::uint8_t DecompressionInputStream::ReadByte()
{
	return m_stream->ReadByte();
}

std::streamsize DecompressionInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	char* buffer = new char[size];
	char* decompressed = new char[8192];
	std::streamsize gcount{ m_stream->ReadBlock(buffer, size) };

	size_t decompressedSize{ m_compressor->Decompress(decompressed, buffer, gcount) };
	memcpy(dstBuffer, decompressed, decompressedSize);

	delete[] buffer;
	delete[] decompressed;

	return decompressedSize;
}