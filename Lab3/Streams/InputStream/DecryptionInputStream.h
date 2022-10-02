#pragma once
#include "Cryptography/ICryptographer.h"
#include "IInputStream.h"

class DecryptionInputStream : public IInputStream
{
public:
	DecryptionInputStream(InputStreamPtr&& stream, const ICryptographer& cryptographer);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	void DecryptBlock(char* dst, char* src, std::streamsize size);

	InputStreamPtr m_stream;
	const ICryptographer& m_cryptographer;
};
