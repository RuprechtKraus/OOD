#include "EncryptionOutputStreamDecorator.h"

EncryptionOutputStreamDecorator::EncryptionOutputStreamDecorator(
	OutputStreamPtr&& stream, const ICryptographer& cryptographer)
	: m_stream(std::move(stream))
	, m_cryptographer(cryptographer)
{
}

void EncryptionOutputStreamDecorator::WriteByte(uint8_t data)
{
	m_stream->WriteByte(m_cryptographer.Encrypt(data));
}

void EncryptionOutputStreamDecorator::WriteBlock(const void* srcData, std::streamsize size)
{
	char* buffer = new char[size];
	EncryptBlock(buffer, static_cast<const char*>(srcData), size);
	m_stream->WriteBlock(buffer, size);
	delete[] buffer;
}

void EncryptionOutputStreamDecorator::EncryptBlock(char* dst, const char* src, std::streamsize size)
{
	for (std::streamsize i = 0; i < size; i++)
	{
		dst[i] = m_cryptographer.Encrypt(src[i]);
	}
}