#pragma once
#include "Cryptography/ICryptographer.h"
#include "IOutputStream.h"

class EncryptionOutputStream : public IOutputStream
{
public:
	EncryptionOutputStream(
		OutputStreamPtr&& stream, std::unique_ptr<ICryptographer>&& cryptographer);
	void WriteByte(uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	void EncryptBlock(char* dst, const char* src, std::streamsize size);

	OutputStreamPtr m_stream;
	std::unique_ptr<ICryptographer> m_cryptographer;
};