#include "DecryptionInputStream.h"

DecryptionInputStream::DecryptionInputStream(
	InputStreamPtr&& stream, std::unique_ptr<ICryptographer>&& cryptographer)
	: m_stream(std::move(stream))
	, m_cryptographer(std::move(cryptographer))
{
}

bool DecryptionInputStream::IsEOF() const
{
	return m_stream->IsEOF();
}

std::uint8_t DecryptionInputStream::ReadByte()
{
	return m_cryptographer->Decrypt(m_stream->ReadByte());
}

std::streamsize DecryptionInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	char* buffer = new char[size];
	std::streamsize gcount{ m_stream->ReadBlock(buffer, size) };
	DecryptBlock(buffer, buffer, size);
	std::memcpy(dstBuffer, buffer, size);
	delete[] buffer;

	return gcount;
}

void DecryptionInputStream::DecryptBlock(char* dst, char* src, std::streamsize size)
{
	for (std::streamsize i = 0; i < size; i++)
	{
		dst[i] = m_cryptographer->Decrypt(src[i]);
	}
}