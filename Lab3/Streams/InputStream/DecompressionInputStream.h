#pragma once
#include "IInputStream.h"
#include <queue>

class DecompressionInputStream : public IInputStream
{
public:
	DecompressionInputStream(InputStreamPtr&& stream);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	uint8_t GetNextBufferedByte() noexcept;
	void BufferByteNTimes(uint8_t byte, int count = 1);
	void VerifyAndSkipNextLexem(uint8_t expectedLexem, bool throwOnEOF = false);
	int ReadBytesCount();

	InputStreamPtr m_stream;
	std::queue<uint8_t> m_buffer;
};
