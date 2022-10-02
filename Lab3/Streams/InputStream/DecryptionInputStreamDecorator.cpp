#include "DecryptionInputStreamDecorator.h"

DecryptionInputStreamDecorator::DecryptionInputStreamDecorator(
	InputStreamPtr&& stream, const ICryptographer& cryptographer)
	: m_stream(std::move(stream))
	, m_cryptographer(cryptographer)
{
}

bool DecryptionInputStreamDecorator::IsEOF() const
{
	return m_stream->IsEOF();
}

std::uint8_t DecryptionInputStreamDecorator::ReadByte()
{
	return m_cryptographer.Decrypt(m_stream->ReadByte());
}

std::streamsize DecryptionInputStreamDecorator::ReadBlock(void* dstBuffer, std::streamsize size)
{
	char* buffer = new char[size];
	std::streamsize gcount{ m_stream->ReadBlock(buffer, size) };
	DecryptBlock(buffer, buffer, size);
	std::memcpy(dstBuffer, buffer, size);
	delete[] buffer;

	return gcount;
}

void DecryptionInputStreamDecorator::DecryptBlock(char* dst, char* src, std::streamsize size)
{
	for (std::streamsize i = 0; i < size; i++)
	{
		dst[i] = m_cryptographer.Decrypt(src[i]);
	}
}