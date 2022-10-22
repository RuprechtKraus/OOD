#pragma once
#include "IInputStream.h"

class DecompressionInputStream : public IInputStream
{
private:
	struct Block
	{
		uint8_t byte;
		uint8_t count;
	};

public:
	DecompressionInputStream(InputStreamPtr&& stream);

	bool IsEOF() const override;
	std::uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	InputStreamPtr m_stream;
	Block m_block{};
};
