#pragma once
#include "Cryptography/ICryptographer.h"
#include "IOutputStream.h"

class EncryptionOutputStreamDecorator : public IOutputStream
{
public:
	EncryptionOutputStreamDecorator(OutputStreamPtr&& stream, const ICryptographer& cryptographer);
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	void EncryptBlock(char* dst, const char* src, std::streamsize size);

	OutputStreamPtr m_stream;
	const ICryptographer& m_cryptographer;
};